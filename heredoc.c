
#include "minishell.h"

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

static void	free_kid_command(t_child *kid, t_here *doc)
{
	int		len;
	int		i;
	int		x;
	char	**tmp;

	i = 0;
	x = 0;
	len = size_2d(kid->commands);
	tmp = (char **)malloc((len - doc->len) * sizeof(char *));
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

void	set_pipe_cmd(t_child *kid, t_here *doc, char *buf)
{
	int	pipes[2];

	free_kid_command(kid, doc);
	if (kid->input_fd != -1)
		close(kid->input_fd);
	pipe(pipes);
	kid->input_fd = dup(pipes[0]);
	write(pipes[1], buf, ft_strlen(buf));
	close(pipes[1]);
	free(buf);
	if (doc->order)
		free_double_array(doc->order);
	free(doc);
	sig_controler(SIG_DEFAULT);
	return ;
}

int	heredoc(t_child *kid)
{
	t_here	*doc;
	int		len;
	char	*buf;

	doc = malloc(sizeof(t_here));
	if (!doc)
		return (0);
	init_doc_struct(doc);
	len = is_valid_heredoc(kid, doc);
	sig_controler(SIG_HEREDOC);
	if (len == -1)
	{
		free(doc);
		sig_controler(SIG_DEFAULT);
		return (-2);
	}
	doc->len = len;
	buf = NULL;
	make_order(kid, doc);
	buf = make_heredoc_line(kid, doc, buf);
	set_pipe_cmd(kid, doc, buf);
	return (-1);
}

void	search_for_heredoc(t_child *kid)
{
	int	check;
	int	y;

	y = 0;
	while(kid->commands[y])
	{
		if (ft_strcmp(kid->commands[y], "<<") == 0 && kid->in_quotes[y] != 'q')
		{
			check = heredoc(kid);
			if(check == -2)
			{
				kid->guard_fork = 1;
				break ;
			}
			y += check;
		}
		y++;
	}
	return ;
}
