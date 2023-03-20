#include "../minishell.h"

void	secure_pwd(t_data *data, char *path)
{
	if (data->saved_pwd)
		free(data->saved_pwd);
	data->saved_pwd = ft_strdup(path);
	return ;
}

static void	ft_cd_back(t_data *data, char *pwd, char *new_path)
{
	char	*tmp;

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
	env_list_to_matrix(data);
	return ;
}

void	save_pwd(t_data *data, char *pwd, char *path)
{
	char	*new_path;

	if (!path)
		return ;
	if (!ft_strcmp(path, ".."))
	{
		new_path = ft_strdup(data->saved_pwd);
		ft_cd_back(data, pwd, new_path);
		return ;
	}
	else
	{
		if (remove_last_char(data, pwd, path))
			return ;
	}
	env_list_to_matrix(data);
	return ;
}
