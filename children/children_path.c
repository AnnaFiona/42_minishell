#include "../minishell.h"

static int	is_double_char(char *path, char c)
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

static char	**get_paths_var(t_data *data)
{
	char	**paths;
	char	*path_line;

	path_line = ft_getenv(data, "PATH");
	if (path_line == NULL)
		return (NULL);
	paths = ft_split(path_line, ':');
	free(path_line);
	return (paths);
}

static char	*access_path(char **paths, char *command)
{
	char	*path_with_command;
	char	*temp_path;
	int		y;

	y = 0;
	while (paths[y])
	{
		temp_path = ft_strjoin(paths[y], "/");
		path_with_command = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(path_with_command, X_OK) == 0)
		{
			if (is_double_char(path_with_command, '/') == 1)
			{
				free_double_array(paths);
				return (path_with_command);
			}
		}
		free(path_with_command);
		y++;
	}
	return (NULL);
}

char	*get_path(t_data *data, t_child *kid, char *command)
{
	char	**paths;
	char	*path_with_command;
	char	*cmd_absolute;

	if (command[0] == '\0')
		return (NULL);
	cmd_absolute = is_absolute_path(data, kid, command);
	if (cmd_absolute)
		return (cmd_absolute);
	paths = get_paths_var(data);
	if (!paths)
		return (NULL);
	path_with_command = access_path(paths, command);
	if (path_with_command)
		return (path_with_command);
	free_double_array(paths);
	return (NULL);
}
