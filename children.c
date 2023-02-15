#include "minishell.h"

void	child_process(t_data *data, char **commands, int input_fd, int output_fd)
{
	char	*path;

	path = NULL;
	if (input_fd != -1)
		dup2(input_fd, STDIN_FILENO);
	if (output_fd != -1)
		dup2(output_fd, STDOUT_FILENO);
	path = get_path(data->path, commands[0]);
	if (path == NULL)
	{
		ft_printf("%s: command not found\n", commands[0]);
		exit_function(data, NULL, 1);
	}
	execve(path, commands, data->env);
}

void	make_child(t_data *data)
{
	char	**commands;
	int		pipe_fd[2];
	int		child_count;
	int		input_fd;
	int		pid;

	input_fd = -1;
	child_count = 0;
	commands = NULL;
	while (child_count <= data->pipe_count)
	{
		if (child_count == data->pipe_count)
			pipe_fd[1] = -1;
		else
			pipe(pipe_fd);
		commands = get_commands(data, data->args);
		pid = fork();
		if (pid == 0)
			child_process(data, commands, input_fd, pipe_fd[1]);
		free(commands);
		commands = NULL;
		if (child_count != 0)
			close (input_fd);
		input_fd = dup(pipe_fd[0]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		child_count++;
	}
	close (input_fd);
	return ;
}

void	redirect_children(t_data *data)
{
	if (data->args == NULL)
		return ;
	data->args_y = 0;
	make_child(data);
	sig_controler(2);
	wait_for_children(data);
	return ;
}