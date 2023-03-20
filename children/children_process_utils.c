#include "../minishell.h"

void	close_pipes_and_free(t_data *data, t_child *kid)
{
	if (kid->commands != NULL)
	{
		free_double_array(kid->commands);
		kid->commands = NULL;
		free(kid->in_quotes);
		kid->in_quotes = NULL;
	}
	if (kid->count != 0 && kid->input_fd != -1)
		close(kid->input_fd);
	if (kid->count != data->pipe_count)
		kid->input_fd = dup(kid->pipe_fd[0]);
	if (kid->pipe_fd[0] != -1)
		close(kid->pipe_fd[0]);
	if (kid->count != data->pipe_count)
		close(kid->pipe_fd[1]);
	if (kid->output_fd != -1)
		close(kid->output_fd);
	return ;
}

void	malloc_pid(t_data *data, t_child *kid)
{
	int	i;

	i = 0;
	kid->pid = malloc(sizeof(int) * (data->pipe_count + 1));
	if (!kid->pid)
		malloc_exit(data, kid);
	while (i <= data->pipe_count)
	{
		kid->pid[i] = -1;
		i++;
	}
	return ;
}

static void	clone_pipe_out(t_child *kid)
{
	if (kid->pipe_fd[0] != -1)
		close(kid->pipe_fd[0]);
	if (kid->pipe_fd[1] != -1 && kid->output_fd == -1)
	{
		kid->output_fd = dup(kid->pipe_fd[1]);
		close(kid->pipe_fd[1]);
	}
	return ;
}

void	dup_input_output(t_child *kid)
{
	int	out;
	int	in;

	clone_pipe_out(kid);
	if (kid->input_fd != -1)
	{
		in = dup2(kid->input_fd, STDIN_FILENO);
		close(kid->input_fd);
		kid->input_fd = dup(in);
	}
	if (kid->output_fd != -1)
	{
		out = dup2(kid->output_fd, STDOUT_FILENO);
		close(kid->output_fd);
		kid->output_fd = dup(out);
	}
	return ;
}

void	change_pwd_mode(t_data *data, t_child *kid)
{
	if (!kid->commands)
		return ;
	if (!ft_strcmp(kid->commands[0], "cd"))
	{
		free_kid(kid);
		exit_function(data, NULL, 3);
	}
	return ;
}
