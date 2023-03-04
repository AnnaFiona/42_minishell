#include "../minishell.h"

static void	initialize_child(t_child *kid)
{
	kid->doc_matrix = NULL;
	kid->commands = NULL;
	kid->in_quotes = NULL;
	kid->pipe_fd = NULL;
	kid->pipe_fd = malloc(sizeof(int) * 2);
	kid->outfile_fd = -1;
	kid->guard_fork = 0;
	kid->infile_fd = -1;
	kid->input_fd = -1;
	kid->count = 0;
	kid->pid = NULL;
	return ;
}

static void	close_pipes_and_free(t_data *data, t_child *kid)
{
	free_double_array(kid->commands);
	kid->commands = NULL;
	free(kid->in_quotes);
	kid->in_quotes = NULL;
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

static void	dup_input_output(t_data *data, t_child *kid, int output_fd)
{
	search_for_arrows(data, kid);
	if (kid->input_fd != -1)
		dup2(kid->input_fd, STDIN_FILENO);
	if (kid->outfile_fd != -1)
		dup2(kid->outfile_fd, STDOUT_FILENO);
	else if (output_fd != -1)
		dup2(output_fd, STDOUT_FILENO);
	if (!kid->commands[0])
	{
		free_kid(kid);
		exit_function(data, NULL, 0);
	}
	return ;
}

static void	child_process(t_data *data, t_child *kid, int output_fd)
{
	char	*path;

	path = NULL;
	sig_controler(SIG_KID);
	//child_ccl(data, kid);
	dup_input_output(data, kid, output_fd);
	if(!ft_strcmp(kid->commands[0], "export"))
	{
		if (kid->commands[1] == NULL)
			sort_env(data, data->env);
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	path = get_path(data, kid, data->path, kid->commands[0]);
	if (path == NULL)
	{
		write (2, kid->commands[0], ft_strlen(kid->commands[0]));
		write (2, ": command not found\n", 20);
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	execve(path, kid->commands, data->env);
}

static void	make_child(t_data *data, t_child *kid)
{
	t_index_doc *my_doc;

	my_doc = malloc(sizeof(t_index_doc) * (data->pipe_count + 1));
	malloc_pid(data, kid);
	get_heredoc_line(data, kid, my_doc);
	while (kid->count <= data->pipe_count)
	{
		if (kid->count == data->pipe_count)
			kid->pipe_fd[1] = -1;
		else
			pipe(kid->pipe_fd);
		get_commands(data, kid, data->args);
		if (kid->commands == NULL)
			break ;
		if(my_doc[kid->count].cut_len > -1)
		{
			free_kid_command(kid, &my_doc[kid->count]);
			set_pipe_cmd(kid, &my_doc[kid->count]);
		}
		//search_for_heredoc(data, kid);
		if (kid->guard_fork == 1)
			break ;
		sig_controler(SIG_PARRENT);
		kid->pid[kid->count] = fork();
		if (kid->pid[kid->count] == 0)
		{
			free(my_doc);
			child_process(data, kid, kid->pipe_fd[1]);
		}
		//data->ccl_token = 0;
		close_pipes_and_free(data, kid);
		kid->count++;
	}
	if (kid->input_fd != -1)
		close(kid->input_fd);
	free(my_doc);
	return ;
}

void	redirect_children(t_data *data)
{
	t_child	*kid;

	kid = malloc(sizeof(t_child));
	if(!kid)
		return ;
	initialize_child(kid);
	if (data->args == NULL)
		return ;
	data->args_y = 0;
	make_child(data, kid);
	wait_for_children(data, kid);
	free_kid(kid);
	sig_controler(SIG_DEFAULT);
	return ;
}
