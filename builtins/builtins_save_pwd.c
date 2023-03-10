
#include "../minishell.h"

/* static void	ft_is_dir(t_data *data)
{
	DIR	*fd;

    if(!data->saved_pwd)
	{
        return ;
	}
	fd = opendir(data->saved_pwd);
	if (!fd)
	{
        free(data->saved_pwd);
        data->saved_pwd = NULL;
        return ;
	}
	closedir(fd);
    return ;
} */

void	ft_save_pwd(t_data *data, char *value)
{
	if (!ft_strcmp(data->args[1], "PWD"))
	{
		if (data->saved_pwd)
			return ;
		data->saved_pwd = ft_strdup(value);
	}
	return ;
}