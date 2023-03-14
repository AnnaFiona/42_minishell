
#include "../minishell.h"

static void	save_home_in_env(t_data *data, char *path)
{
	char	*old_path;

	old_path = NULL;
	secure_pwd(data, path);
	old_path = ft_getenv(data, "PWD");
	save_pwd(data, "OLDPWD", old_path);
	save_pwd(data, "PWD", path);
	if (old_path)
		free(old_path);
	if (path)
		free(path);
	return ;
}

static void	ft_cd_home(t_data *data)
{
	char	*path;

	path = NULL;
	path = ft_getenv(data, "HOME");
	if (!path)
	{
		data->exit_status = 1;
		ft_printf("minishell: cd: HOME not set\n");
	}
	else if (chdir_error_msg(data, path))
		free(path);
	else
		save_home_in_env(data, path);
	return ;
}

static void	save_and_free(t_data *data, char *old_pwd, char *path)
{
	save_pwd(data, "OLDPWD", old_pwd);
	save_pwd(data, "PWD", path);
	if (old_pwd)
		free(old_pwd);
	if (path)
		free(path);
	return ;
}

static void	cd_pipe_error_msg(t_data *data, t_child *kid)
{
	DIR	*fd;

	if (!kid->commands[1] || kid->commands[1][0] == '\0'
		|| !ft_strcmp(kid->commands[1], ".."))
	{
		data->exit_status = 0;
		return ;
	}
	fd = opendir(kid->commands[1]);
	if (!fd)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n",
			kid->commands[1]);
		data->exit_status = 1;
		return ;
	}
	closedir(fd);
	return ;
}

int	ft_cd(t_data *data, t_child *kid, char *argv)
{
	char	*path;
	char	*old_pwd;

	if (data->pipe_count > 0)
	{
		cd_pipe_error_msg(data, kid);
		return (0);
	}
	data->exit_status = 0;
	if (!argv || argv[0] == '\0')
	{
		ft_cd_home(data);
		return (0);
	}
	path = NULL;
	old_pwd = NULL;
	if (chdir_error_msg(data, argv))
		return (0);
	path = ft_strdup(argv);
	old_pwd = ft_getenv(data, "PWD");
	if (!(path[0] == '/') && ft_strcmp(path, ".."))
		path = save_relative_path(old_pwd, path);
	save_and_free(data, old_pwd, path);
	return (0);
}
