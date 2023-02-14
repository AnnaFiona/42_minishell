#include "minishell.h"

void	one_command(t_data *data)
{
	char	**commands;
	char	*path;
	int		pid;

	commands = NULL;
	pid = fork();
	if (pid != 0)
		return ;
	sig_controler(1);
	path = get_path(data->path, data->args[0]);
	if (path == NULL)
	{
		ft_printf("%s: command not found\n", data->args[0]);
		exit_function(data, NULL, 1);
	}
	commands = get_commands(data, data->args, 0);
	//print_double_array(commands);
	execve(path, commands, data->env);
}

void	redirect_children(t_data *data)
{
	if (data->args == NULL)
		return ;
	//count_pipes(data);
	if (data->pipe_count == 0)
		one_command(data);
	sig_controler(2);
	data->pipe_count++;
	wait_for_children(data);
	
	//else if ()
}