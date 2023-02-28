#include "../minishell.h"

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
		waitpid(-1, &data->exit_status, 0);
		data->pipe_count--;
	}
	if (data->exit_status == 2)
		data->exit_status = 130;
	if (data->exit_status == 256)
		data->exit_status = 127;
	if (data->exit_status == 512)
		data->exit_status = 2;
	if (data->exit_status == 768)
		data->exit_status = 1;
	return ;
}
