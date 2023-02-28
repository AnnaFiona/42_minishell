
#include "minishell.h"

static int	count_fill_order(t_child *kid, t_here *doc, char fill)
{
	int	i;
	int x;

	i = 0;
	x = 0;
	while (kid->commands[i] && i < doc->range)
	{
		if (!ft_strcmp(kid->commands[i], "<<") && kid->commands[i + 1])
		{
			i++;
			if (fill == 'y')
				doc->order[x] = ft_strdup(kid->commands[i]);
			x++;
		}
		i++;
	}
	doc->arrows = x;
	if (fill == 'y')
		doc->order[x] = NULL;
	return (x);
}

void	make_order(t_child *kid, t_here *doc)
{
	int	i;

	i = count_fill_order(kid, doc, 'n');
	doc->order = malloc(sizeof(char *) * (i + 1));
	if (!doc->order)
		return ;
	count_fill_order(kid, doc, 'y');
	return ;
}

static int	join_error_handling(t_child *kid, t_here *doc, int line_count)
{
	doc->line = readline("> ");
	if (!doc->line)
	{
		if(global_in_fd_copy == 0)
		{
			ft_printf("bash: warning: here-document at line");
			ft_printf(" %i delimited by end-of-file ", line_count);
			ft_printf("(wanted `%s')\n", kid->commands[doc->len + 1]);
			kid->guard_fork = 1;
			sig_controler(SIG_DEFAULT);
			return (0);
		}
		write(1, "\n", 1);
		dup2(global_in_fd_copy, 0);
		global_in_fd_copy = 0;
		kid->guard_fork = 1;
		sig_controler(SIG_DEFAULT);
		return(0);
	}
	return (1);
}

static int	start_stop(t_here *doc)
{
	if (doc->arrows == 1)
	{
		if (doc->order && doc->index == size_2d(doc->order))
			return (0);
		return (ft_strcmp(doc->line, doc->order[doc->index]));
	}
	else
	{
		if (doc->order && doc->index == size_2d(doc->order))
			return (0);
	}
	return (1);
}

static void	is_order(t_here *doc)
{
	if(!ft_strcmp(doc->line, doc->order[doc->index]))
	{
		doc->token = 1;
		doc->index++;
		free(doc->line);
		doc->line = NULL;
	}
	else if(doc->token == 0 && doc->arrows > 1)
	{
		free(doc->line);
		doc->line = NULL;
	}
}

char	*make_heredoc_line(t_child *kid, t_here *doc, char *buf)
{
	int		len;
	int		line_count;
	int		doc_exit_line;
	char	*line_nl;

	len = 0;
	line_count = 0;
	doc_exit_line = 0;
	line_nl = NULL;
	while (start_stop(doc) != 0)
	{
		if (doc->line)
			free(doc->line);
		line_count++;
		if (join_error_handling(kid, doc, line_count) == 0)
			break ;
		is_order(doc);
		line_nl = ft_strjoin(doc->line, "\n");
		buf = join_free(buf, line_nl);
	}
	if (doc->line)
		free(doc->line);
	return (buf);
}