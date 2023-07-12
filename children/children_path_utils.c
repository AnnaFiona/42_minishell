#include "../minishell.h"

static void	is_dir(t_data *data, t_child *kid, char *cmd)
{
	DIR	*fd;

	fd = opendir(cmd);
	if (fd)
	{
		closedir(fd);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free_kid(kid);
		exit_function(data, NULL, 4);
	}
	return ;
}

char	*is_absolute_path(t_data *data, t_child *kid, char *cmd)
{
	if (access(cmd, X_OK) != 0)
		return (NULL);
	is_dir(data, kid, cmd);
	return (cmd);
}
