#include "../minishell.h"

static void	initialize_child(t_child *kid)
{
	kid->doc_matrix = NULL;
	kid->commands = NULL;
	kid->in_quotes = NULL;
	kid->pipe_fd = NULL;
	kid->pipe_fd = malloc(sizeof(int) * 2);
	if (!kid->pipe_fd)
		malloc_exit(NULL, kid);
	kid->pipe_fd[0] = -1;
	kid->pipe_fd[1] = -1;
	kid->output_fd = -1;
	kid->input_fd = -1;
	kid->no_fork = 0;
	kid->count = 0;
	kid->pid = NULL;
	return ;
}

static void	pipe_controller(t_data *data, t_child *kid, t_index_doc *my_doc)
{
	if (kid->count == data->pipe_count)
		kid->pipe_fd[1] = -1;
	else
		pipe(kid->pipe_fd);
	get_commands(data, kid, data->args);
	if (kid->commands == NULL)
		return ;
	if (data->guard_fork != 1)
		search_for_arrows(data, kid);
	if (kid->no_fork == 1)
		return ;
	if (my_doc[kid->count].cut_len > -1)
	{
		free_kid_command(kid, &my_doc[kid->count]);
		set_pipe_cmd(kid, &my_doc[kid->count]);
	}
	return ;
}

static void	should_fork(t_data *data, t_child *kid, t_index_doc	*my_doc)
{
	if (builtins_in_kid(data, kid) == MAKE_CHILDS)
	{
		sig_controler(SIG_PARRENT);
		kid->pid[kid->count] = fork();
		if (kid->pid[kid->count] == 0)
		{
			free_line(data, my_doc);
			free(my_doc);
			clear_history();
			child_process(data, kid);
		}
	}
	return ;
}

static void	make_child(t_data *data, t_child *kid)
{
	t_index_doc	*my_doc;

	my_doc = malloc(sizeof(t_index_doc) * (data->pipe_count + 1));
	if (!my_doc)
		malloc_exit(data, kid);
	malloc_pid(data, kid);
	get_heredoc_line(data, kid, my_doc);
	while (kid->count <= data->pipe_count)
	{
		pipe_controller(data, kid, my_doc);
		if (data->guard_fork == 1)
			break ;
		if (builtins_in_kid(data, kid) == MAKE_CHILDS)
			should_fork(data, kid, my_doc);
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
	if (!kid)
		malloc_exit(data, NULL);
	initialize_child(kid);
	if (data->args == NULL)
		return ;
	data->args_y = 0;
	make_child(data, kid);
	wait_for_children(data, kid);
	set_exit_status(data);
	free_kid(kid);
	sig_controler(SIG_DEFAULT);
	return ;
}
