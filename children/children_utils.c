#include "../minishell.h"	

int	count_pipes(t_data *data)
{
	int	y;

	y = 0;
	data->pipe_count = 0;
	while (data->args[y])
	{
		if (ft_strcmp(data->args[y], "|") == 0)
			data->pipe_count++;
		y++;
	}
	return (0);
}

static void	copy_commands(t_data *data, t_child *kid, char **args)
{
	int	x;

	x = 0;
	while (args[data->args_y] && !(args[data->args_y][0] == '|'
		&& data->in_quotes[data->args_y] == '-'))
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
	while (args[data->args_y] && !(args[data->args_y][0] == '|'
		&& data->in_quotes[data->args_y] == '-'))
	{
		data->args_y++;
		x++;
	}
	data->args_y -= x;
	if (x == 0)
	{
		data->args_y++;
		return ;
	}
	kid->commands = malloc(sizeof(char *) * (x + 1));
	kid->in_quotes = malloc(sizeof(char) * (x + 1));
	if (!kid->commands || !kid->in_quotes)
		malloc_exit(data, kid);
	if (!kid->commands || !kid->in_quotes)
		exit_function(data, "Error: malloc failed", 12);
	copy_commands(data, kid, args);
	if (args[data->args_y] != NULL && args[data->args_y][0] == '|')
		data->args_y++;
	return ;
}

void	wait_for_children(t_data *data, t_child *kid)
{
	int	i;

	i = 0;
	if (data->guard_fork == 1)
		return ;
	while (i <= data->pipe_count)
	{
		if (kid->pid[i] != -1)
		{
			if (i == data->pipe_count)
				waitpid(kid->pid[i], &data->exit_status, 0);
			else
				waitpid(kid->pid[i], NULL, 0);
		}
		i++;
	}
	return ;
}

void	set_exit_status(t_data *data)
{
	if (data->guard_fork == 1)
		return ;
	if (data->exit_status == 2)
		data->exit_status = 130;
	else if (data->exit_status == 139)
		ft_printf("Segmentation fault (core dumped)\n");
	else if (data->exit_status == 256)
		data->exit_status = 1;
	else if (data->exit_status == 512)
		data->exit_status = 2;
	else if (data->exit_status == 768)
		data->exit_status = 127;
	else if (data->exit_status == 1024)
		data->exit_status = 126;
	else if (data->exit_status != 0 && data->exit_status != 1 \
			&& data->exit_status != 131)
		data->exit_status = 255;
	return ;
}
