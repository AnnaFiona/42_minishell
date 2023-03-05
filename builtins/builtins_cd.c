
#include "../minishell.h"

static int	remove_end_malloc(char *str, char c)
{
	int	count;
	int	len;

	len = 0;
	count = 0;
	while (str[len])
	{
		if (str[len] == '/')
			count++;
		if (count > 1)
			break ;
		len++;
	}
	if (count < 2)
		return (-1);
	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == c)
			break ;
		len--;
	}
	return (len);
}

static char	*remove_end(char *str, char c)
{
	int		i;
	int		len;
	char	*tmp;

	if (!str)
		return (NULL);
	if (!ft_strcmp(str, "/"))
		return (str);
	i = 0;
	len = remove_end_malloc(str, c);
	if (len == -1)
	{
		free(str);
		str = malloc(sizeof(char) * 2);
		str[0] = '/';
		str[1] = '\0';
		return (str);
	}
	tmp = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

static void	save_pwd(t_data *data, char *pwd, char *path)
{
	char	*new_path;
	char	*tmp;

	if (!path)
		return ;
	if (!ft_strcmp(path, ".."))
	{
		new_path = ft_getenv(data, "PWD");
		if (!ft_strcmp(new_path, "/"))
		{
			free(new_path);
			return ;
		}
		tmp = remove_end(new_path, '/');
		if (!tmp)
			return ;
		is_dublicate(data, pwd, tmp);
		free(tmp);
	}
	else
	{
		if (is_last_char(path, '/') == 0)
		{
			tmp = rm_last_char(path);
			is_dublicate(data, pwd, tmp);
			free(tmp);
			env_list_to_matrix(data);
			return ;
		}
		is_dublicate(data, pwd, path);
	}
	env_list_to_matrix(data);
	return ;
}

static void	ft_cd_home(t_data *data)
{
	char	*path;
	char	*old_path;

	path = NULL;
	old_path = NULL;
	path = ft_getenv(data, "HOME");
	if (!path)
		ft_printf("minishell: cd: HOME not set\n");
	else if (chdir(path))
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
	else
	{
		old_path = ft_getenv(data, "PWD");
		save_pwd(data, "OLDPWD", old_path);
		save_pwd(data, "PWD", path);
		free(old_path);
		free(path);
	}
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

int	ft_cd(t_data *data, char *argv)
{
	char	*path;
	char	*old_pwd;

	if (!argv)
	{
		ft_cd_home(data);
		return (0);
	}
	path = NULL;
	old_pwd = NULL;
	path = ft_strdup(argv);
	if (chdir(argv))
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", argv);
		return (0);
	}
	old_pwd = ft_getenv(data, "PWD");
	if (!(path[0] == '/') && ft_strcmp(path, ".."))
		path = save_relative_path(old_pwd, path);
	save_and_free(data, old_pwd, path);
	return (0);
}
