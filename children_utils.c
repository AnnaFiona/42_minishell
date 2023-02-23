#include "minishell.h"

void	count_pipes(t_data *data)
{
	int	y;

	y = 0;
	data->pipe_count = 0;
	while (data->args[y])
	{
		if (data->args[y][0] == '|' && data->in_quotes[y] != 'q')
			data->pipe_count++;
		y++;
	}
	return ;
}

char	*get_path(char **paths, char *command)
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

static void	copy_commands(t_data *data, t_child *kid, char **args)
{
	int	x;

	x = 0;
	while (args[data->args_y] && !(args[data->args_y][0] == '|' && data->in_quotes[data->args_y] == '-'))
	{
		kid->commands[x] = ft_strdup(args[data->args_y]);
		kid->in_quotes[x] = data->in_quotes[data->args_y];
		data->args_y++;
		x++;
	}
	kid->commands[x] = NULL;
	kid->in_quotes[x] = '\0';
	ft_printf("kid->in_quotes: %s\nx: %d\n", kid->in_quotes, x);
	return ;
}

void	get_commands(t_data *data, t_child *kid, char **args)
{
	int	x;

	x = 0;
	while (args[data->args_y] && !(args[data->args_y][0] == '|' && data->in_quotes[data->args_y] == '-'))
	{
		data->args_y++;
		x++;
	}
	data->args_y -= x;
	if (x == 0)
		return ;//protect!!!!
	kid->commands = malloc(sizeof(char *) * (x + 1));
	kid->in_quotes = malloc(sizeof(char) * (x + 1));
	if (!kid->commands || !kid->in_quotes)
		exit_function(data, "Error: malloc failed at \"get_commands\" \
		in \"children_utils.c\"", 1);
	copy_commands(data, kid, args);
	if (args[data->args_y] != NULL && args[data->args_y][0] == '|')
		data->args_y++;
	return ;
}

void	wait_for_children(t_data *data)
{
	data->pipe_count++;
	while (data->pipe_count > 0)
	{
		waitpid(-1, NULL, 0);
		data->pipe_count--;
	}
}
