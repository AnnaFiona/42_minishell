
#include "../minishell.h"

static void	ft_is_dir(char *new_path)
{
	DIR	*fd;

	if (!new_path)
	{
		return ;
	}
	fd = opendir(new_path);
	if (!fd)
	{
		free(new_path);
		new_path = NULL;
		return ;
	}
	closedir(fd);
	return ;
}

void	secure_pwd(t_data *data, char *path)
{
	if (data->saved_pwd)
		free(data->saved_pwd);
	data->saved_pwd = ft_strdup(path);
	return ;
}

static char	*is_path_unset(t_data *data)
{
	char	*path;

	if (data->saved_pwd)
	{
		path = ft_strdup(data->saved_pwd);
		return (path);
	}
	return (NULL);
}

void	save_pwd(t_data *data, char *pwd, char *path)
{
	char	*new_path;
	char	*tmp;

	if (!path)
		return ;
	if (!ft_strcmp(path, ".."))
	{
		new_path = ft_getenv(data, "PWD");
		ft_is_dir(new_path);
		if (!new_path)
			new_path = is_path_unset(data);
		if (!ft_strcmp(new_path, "/"))
		{
			secure_pwd(data, "/");
			free(new_path);
			return ;
		}
		tmp = remove_end(new_path, '/');
		if (!tmp)
			return ;
		secure_pwd(data, tmp);
		is_dublicate(data, pwd, tmp);
		free(tmp);
	}
	else
	{
		if (is_last_char(path, '/') == 0)
		{
			tmp = rm_last_char(path);
			secure_pwd(data, path);
			is_dublicate(data, pwd, tmp);
			free(tmp);
			env_list_to_matrix(data, 'x');
			return ;
		}
		is_dublicate(data, pwd, path);
	}
	env_list_to_matrix(data, 'x');
	return ;
}