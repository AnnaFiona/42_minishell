
#include "../minishell.h"

char	*join_free(char *s1, char *s2)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		str = ft_strdup(s2);
		free(s2);
		return (str);
	}
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

void	set_pipe_cmd(t_child *kid, t_index_doc *my_doc)
{
	int	pipes[2];

	if (kid->input_fd != -1)
		close(kid->input_fd);
	pipe(pipes);
	kid->input_fd = dup(pipes[0]);
	write(pipes[1], my_doc->doc_line, ft_strlen(my_doc->doc_line));
	close(pipes[1]);
	if(my_doc->doc_line)
		free(my_doc->doc_line);
	my_doc->doc_line = NULL;
	return ;
}

void	free_kid_command(t_child *kid, t_index_doc *my_doc)
{
	int		len;
	int		i;
	int		x;
	char	**tmp;

	i = 0;
	x = 0;
	len = size_2d(kid->commands);
	tmp = (char **)malloc((len - my_doc->cut_len + 1) * sizeof(char *));
	if (!kid->commands)
		return ;
	while (x < len)
	{
		if (ft_strcmp(kid->commands[x], "<<"))
		{
			tmp[i] = ft_strdup(kid->commands[x]);
			i++;
			x++;
		}
		if (!ft_strcmp(kid->commands[x], "<<"))
			x += 2;
	}
	tmp[i] = NULL;
	free_double_array(kid->commands);
	kid->commands = tmp;
	return ;
}

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


static int	heredoc(t_data *data, t_child *kid, t_index_doc *my_doc)
{
	t_here	*doc;
	int		len;
	//char	*buf;

	doc = malloc(sizeof(t_here));
	if (!doc)
		return (0);
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
	//buf = NULL;
	make_order(kid, doc);
	my_doc->doc_line = make_heredoc_line(kid, doc); 
	free_kid_command(kid, my_doc);
	if (doc->order)
		free_double_array(doc->order);
	free(doc);
	sig_controler(SIG_DEFAULT);
	//set_pipe_cmd(kid, doc, buf);
	return (-1);
}

void	search_for_heredoc(t_data *data, t_child *kid, t_index_doc *my_doc)
{
	int	check;
	int	y;

	y = 0;
	data->exit_status = 130;
	while(kid->commands[y])
	{
		if (ft_strcmp(kid->commands[y], "<<") == 0 && kid->in_quotes[y] != 'q')
		{
			check = heredoc(data, kid, my_doc);
			if(check == -2)
			{
				kid->guard_fork = 1;
				return ;
			}
			y += check;
		}
		y++;
	}
	if (kid->guard_fork != 1)
		data->exit_status = 0;
	return ;
}

void	get_heredoc_line(t_data *data, t_child *kid, t_index_doc *my_doc)
{
	int i;
	//t_index_doc *my_doc;

	i = 0;
	//my_doc = malloc(sizeof(t_index_doc) * data->pipe_count);
	//kid->doc_matrix = malloc(sizeof(char *) * (data->pipe_count + 1));
	while(i <= data->pipe_count)
	{
		my_doc[i].doc_line = NULL;
		my_doc[i].cut_len = -1;
		get_commands(data, kid, data->args);
		search_for_heredoc(data, kid, &my_doc[i]);
		free_double_array(kid->commands);
		free(kid->in_quotes);
		kid->commands = NULL;
		if (kid->guard_fork == 1)
			break ;
		i++;
	}
	/* if(kid->commands)
		free_double_array(kid->commands); */
	kid->commands = NULL;
	data->args_y = 0;
	return ;
}