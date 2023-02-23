
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

//make a valid check!!!!

int is_arrow(t_child *kid)
{
	int i;

	i = 0;
	while(kid->commands[i])
	{
		if(!ft_strcmp(kid->commands[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}

static int	is_valid_heredoc(t_child *kid)
{
	int i;
	int	len;

	i = 0;
	if (!kid->commands)
		return (-1);
	len = 0;
	if (!ft_strcmp(kid->commands[0], "<<") || !kid->commands[1])
		return (-1);
	if(!is_arrow(kid))
		return (-1);
	while (kid->commands[i])
	{
		if(!ft_strcmp(kid->commands[i], "<<") && !ft_strcmp(kid->commands[i + 1], "<<"))
		{
			ft_printf("bash: syntax error near unexpected token `<<'\n");
			if(len == 0)
			{
				free_kid(kid);
				exit(0); 
			}
			return (len);
		}
		if(!ft_strcmp(kid->commands[i], "<<") && !kid->commands[i + 1])
		{
			free_kid(kid);
			exit(0); 
		}
		if(!ft_strcmp(kid->commands[i], "<<"))
			len++;
		i++;
	}
	if (!kid->commands[len])
		return (-1);
	return (len);
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
	print_double_array(kid->commands);
	return ;
}

void init_doc_struct(t_here *doc)
{
	doc->len = 0;
	doc->index = 0;
	doc->token = 0;
	doc->arrows = 0;
	doc->line = NULL;
	doc->order = NULL;
}

int	heredoc(t_child *kid)
{
	t_here *doc;
	int 	len;
	int		pipes[2];
	char	*buf;

	len = is_valid_heredoc(kid);
	if (len == -1)
		return (1);
	doc = malloc(sizeof(t_here));
	if(!doc)
		return (1);
	doc->len = len;
	buf = NULL;
	make_order(kid, doc);
	buf = make_heredoc_line(kid, doc, buf);
	free_kid_command(kid, doc);
	if (kid->input_fd != -1)
		close(kid->input_fd);
	pipe(pipes);
	kid->input_fd = dup(pipes[0]);
	write(pipes[1], buf, ft_strlen(buf));
	close(pipes[1]);
	free(buf);
	return (1);
}
