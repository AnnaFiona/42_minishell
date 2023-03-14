#include "../minishell.h"

static void	init_doc_struct(t_here *doc)
{
	doc->len = 0;
	doc->range = 0;
	doc->index = 0;
	doc->token = 0;
	doc->arrows = 0;
	doc->line = NULL;
	doc->order = NULL;
}

static void	make_order(t_child *kid, t_here *doc)
{
	int	i;

	i = count_fill_order(kid, doc, 'n');
	doc->order = malloc(sizeof(char *) * (i + 1));
	if (!doc->order)
		malloc_exit(NULL, kid);
	count_fill_order(kid, doc, 'y');
	return ;
}

static int	heredoc(t_data *data, t_child *kid, t_index_doc *my_doc)
{
	t_here	*doc;
	int		len;

	doc = malloc(sizeof(t_here));
	if (!doc)
		malloc_exit(data, kid);
	init_doc_struct(doc);
	len = is_valid_heredoc(data, kid, doc);
	sig_controler(SIG_HEREDOC);
	if (len == -1)
	{
		free(doc);
		sig_controler(SIG_DEFAULT);
		return (-2);
	}
	doc->len = len;
	my_doc->cut_len = len;
	make_order(kid, doc);
	my_doc->doc_line = make_heredoc_line(data, kid, doc);
	free_kid_command(kid, my_doc);
	if (doc->order)
		free_double_array(doc->order);
	free(doc);
	sig_controler(SIG_DEFAULT);
	return (-1);
}

static void	search_for_heredoc(t_data *data, t_child *kid, t_index_doc *my_doc)
{
	int	check;
	int	y;

	y = 0;
	data->exit_status = 130;
	while (kid->commands[y])
	{
		if (ft_strcmp(kid->commands[y], "<<") == 0 && kid->in_quotes[y] != 'q')
		{
			check = heredoc(data, kid, my_doc);
			if (check == -2)
			{
				data->guard_fork = 1;
				return ;
			}
			y += check;
		}
		y++;
	}
	if (data->guard_fork != 1)
		data->exit_status = 0;
	return ;
}

void	get_heredoc_line(t_data *data, t_child *kid, t_index_doc *my_doc)
{
	int	i;

	i = 0;
	while (i <= data->pipe_count)
	{
		my_doc[i].doc_line = NULL;
		my_doc[i].cut_len = -1;
		get_commands(data, kid, data->args);
		if (kid->commands)
		{
			search_for_heredoc(data, kid, &my_doc[i]);
			free_double_array(kid->commands);
			kid->commands = NULL;
		}
		if (kid->in_quotes)
		{
			free(kid->in_quotes);
			kid->in_quotes = NULL;
		}
		if (data->guard_fork == 1)
			break ;
		i++;
	}
	kid->commands = NULL;
	data->args_y = 0;
	if (data->guard_fork == 1)
		data->exit_status = 2;
	return ;
}
