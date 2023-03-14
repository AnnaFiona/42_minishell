#include "../minishell.h"

static char	*join_free(char *s1, char *s2)
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

static int	join_error_handling(t_data *data, t_child *kid,
								t_here *doc, int line_count)
{
	doc->line = readline("> ");
	if (!doc->line)
	{
		if (g_in_fd_copy == 0)
		{
			ft_printf("minishell: warning: here-document at line");
			ft_printf(" %i delimited by end-of-file ", line_count);
			ft_printf("(wanted `%s')\n", kid->commands[doc->len + 1]);
			data->guard_fork = 1;
			sig_controler(SIG_DEFAULT);
			return (0);
		}
		write(1, "\n", 1);
		dup2(g_in_fd_copy, 0);
		g_in_fd_copy = 0;
		data->guard_fork = 1;
		sig_controler(SIG_DEFAULT);
		return (0);
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
	if (!ft_strcmp(doc->line, doc->order[doc->index]))
	{
		doc->token = 1;
		doc->index++;
		free(doc->line);
		doc->line = NULL;
	}
	else if (doc->token == 0 && doc->arrows > 1)
	{
		free(doc->line);
		doc->line = NULL;
	}
}

char	*make_heredoc_line(t_data *data, t_child *kid, t_here *doc)
{
	int		len;
	int		line_count;
	int		doc_exit_line;
	char	*buf;
	char	*line_nl;

	len = 0;
	line_count = 0;
	doc_exit_line = 0;
	buf = NULL;
	line_nl = NULL;
	while (start_stop(doc) != 0)
	{
		if (doc->line)
			free(doc->line);
		line_count++;
		if (join_error_handling(data, kid, doc, line_count) == 0)
			break ;
		is_order(doc);
		line_nl = ft_strjoin(doc->line, "\n");
		buf = join_free(buf, line_nl);
	}
	if (doc->line)
		free(doc->line);
	return (buf);
}
