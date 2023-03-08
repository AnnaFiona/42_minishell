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

static char	*is_absolute_path(t_data *data, t_child *kid, char *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (access(cmd, X_OK) != 0)
		return (NULL);
	is_dir(data, kid, cmd);
	return (cmd);
}

int	is_dubble_char(char *path, char c)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == c && path[i + 1] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*get_path(t_data *data, t_child *kid, char **paths, char *command)
{
	char	*path_with_command;
	char	*cmd_absolute;
	char	*temp_path;
	int		y;

	y = 0;
	cmd_absolute = is_absolute_path(data, kid, command);
	if (cmd_absolute)
		return (cmd_absolute);
	while (paths[y])
	{
		temp_path = ft_strjoin(paths[y], "/");
		path_with_command = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(path_with_command, X_OK) == 0)
		{
			if(is_dubble_char(path_with_command, '/') == 1)
				return (path_with_command);
		}
		free(path_with_command);
		y++;
	}
	return (NULL);
}
