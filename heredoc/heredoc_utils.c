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

static int	join_error_handling(t_data *data, t_here *doc)
{
	if (data->guard_fork == 2)
		return (0);
	doc->line = readline("> ");
	if (!doc->line)
	{
		if (g_in_fd_copy == 0)
		{
			ft_printf("minishell: warning: here-document");
			ft_printf(" delimited by end-of-file ");
			ft_printf("(wanted `%s')\n", doc->order[doc->index]);
			sig_controler(SIG_DEFAULT);
			doc->index++;
			return (1);
		}
		write(1, "\n", 1);
		dup2(g_in_fd_copy, 0);
		g_in_fd_copy = 0;
		data->guard_fork = 2;
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
		doc->index++;
		if (size_2d(doc->order) - 1 == doc->index)
			doc->token = 1;
		free(doc->line);
		doc->line = NULL;
	}
	else if (doc->token == 0 && doc->arrows > 1)
	{
		free(doc->line);
		doc->line = NULL;
	}
}

char	*make_heredoc_line(t_data *data, t_here *doc)
{
	int		len;
	int		doc_exit_line;
	char	*buf;
	char	*line_nl;

	len = 0;
	doc_exit_line = 0;
	buf = NULL;
	line_nl = NULL;
	while (start_stop(doc) != 0)
	{
		if (doc->line)
			free(doc->line);
		if (join_error_handling(data, doc) == 0)
			break ;
		is_order(doc);
		line_nl = ft_strjoin(doc->line, "\n");
		buf = join_free(buf, line_nl);
	}
	if (doc->line)
		free(doc->line);
	return (buf);
}
