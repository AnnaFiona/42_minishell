
#include "minishell.h"

int check_order(t_here *doc)
{
	
	return ;
}

int	start_stop(t_data *data, t_here *doc, int len)
{
	if(doc->arrows = 1)
		return(ft_strcmp(doc->line, kid->commands[len + 1]));
	else
	{
		if(!ft_strcmp(doc->line, doc->order[doc->index]))
			doc->index++;
		if(doc->index == ft_strlen(doc->order) - 1)
			return (0);
	}
	return (1);
}

char	*make_heredoc_line(t_child *kid, t_here *doc, char *buf, int len)
{
	int		len;
	char	*line_nl;
	char	*buf;

	len = 0;
	doc->index = 0;
	doc->line = NULL;
	line_nl = NULL;
	while (ft_strcmp(line, kid->commands[len + 1]))
	{
		i++;
		if (doc->line)
			free(doc->line);
		doc->line = readline("> ");
		if (!doc->line)
		{
			ft_printf("bash: warning: here-document at line");
			ft_printf(" %i delimited by end-of-file ", i);
			ft_printf("wanted `%s')\n", kid->commands[len + 1]);
			break ;
		}
		line_nl = ft_strjoin(doc->line, "\n");
		buf = join_free(buf, line_nl);
	}
	if (doc->line)
		free(doc->line);
	return (buf);
}