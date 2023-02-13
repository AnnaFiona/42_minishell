#include "minishell.h"

void	count_pipes(t_data *data)
{
	int	y;

	y = 0;
	data->pipe_count = 0;
	while (data->args[y])
	{
		if (data->args[y][0] == '|')
			data->pipe_count++;
		y++;
	}
	return ;
}

char	*get_path(char	**paths, char *command)
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
			return (path_with_command);
		free (path_with_command);
		y++;
	}
	return (NULL);
}

char	**get_commands(t_data *data, char **args, int y)
{
	char	**commands;
	int		x;

	x = 0;
	commands = NULL;
	while (args[y] && args[y][0] != '|')
	{
		x++;
		y++;
	}
	y -= x;
	commands = malloc(sizeof(char *) * (x + 1));
	ft_printf("x: %d\n", x);
	if (!commands)
		exit_function(data, "Error: malloc failed at \"get_commands\" \
		in \"children_utils.c\"", 1);
	x = 0;
	while (args[y] && args[y][0] != '|')
	{
		commands[x] = ft_strdup(args[y]);
		x++;
		y++;
	}
	commands[x] = NULL;
	print_double_array(commands);
	return (commands);
}

void	wait_for_children(t_data *data)
{
	while (data->pipe_count > 0)
	{
		waitpid(-1, NULL, 0);
		data->pipe_count--;
	}
}
