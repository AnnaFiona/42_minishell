#include "minishell.h"

static void	initialize_child(t_child *kid)
{
	kid->commands = NULL;
	kid->pipe_fd = malloc(sizeof(int) * 2);
	kid->count = 0;
	kid->input_fd = -1;
	kid->pid = -1;
	return ;
}

static void	close_pipes(t_data *data, t_child *kid)
{
	if (kid->count != 0)
		close(kid->input_fd);
	if (kid->count != data->pipe_count)
		kid->input_fd = dup(kid->pipe_fd[0]);
	if (kid->count != 0)
		close(kid->pipe_fd[0]);
	if (kid->count != data->pipe_count)
		close(kid->pipe_fd[1]);
	return ;
}

static void	child_process(t_data *data, t_child *kid, int output_fd)
{
	char	*path;

	path = NULL;
	if (kid->input_fd != -1)
		dup2(kid->input_fd, STDIN_FILENO);
	if (output_fd != -1)
		dup2(output_fd, STDOUT_FILENO);
	if(ft_strcmp(kid->commands[0], "export") == 0)
	{
		sort_env(data, data->env);
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	path = get_path(data->path, kid->commands[0]);
	if (path == NULL)
	{
		ft_printf("%s: command not found\n", kid->commands[0]);
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	execve(path, kid->commands, data->env);
}

static void	make_child(t_data *data)
{
	t_child	*kid;

	kid = malloc(sizeof(t_child));
	initialize_child(kid);
	while (kid->count <= data->pipe_count)
	{
		if (kid->count == data->pipe_count)
			kid->pipe_fd[1] = -1;
		else
			pipe(kid->pipe_fd);
		kid->commands = get_commands(data, data->args);
		kid->pid = fork();
		if (kid->pid == 0)
			child_process(data, kid, kid->pipe_fd[1]);
		free_double_array(kid->commands);
		kid->commands = NULL;
		close_pipes(data, kid);
		kid->count++;
	}
	if (kid->input_fd != -1)
		close(kid->input_fd);
	free_kid(kid);
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
