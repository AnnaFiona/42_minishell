
#include "../minishell.h"

int	count_fill_order(t_child *kid, t_here *doc, char fill)
{
	int	i;
	int	x;

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

void	set_pipe_cmd(t_child *kid, t_index_doc *my_doc)
{
	int	pipes[2];

	if (kid->input_fd != -1)
		close(kid->input_fd);
	pipe(pipes);
	kid->input_fd = dup(pipes[0]);
	write(pipes[1], my_doc->doc_line, ft_strlen(my_doc->doc_line));
	close(pipes[1]);
	if (my_doc->doc_line)
		free(my_doc->doc_line);
	my_doc->doc_line = NULL;
	return ;
}

static void	make_kid_cmd(t_child *kid, char **tmp, int len)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
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
	return ;
}

void	free_kid_command(t_child *kid, t_index_doc *my_doc)
{
	int		len;
	char	**tmp;

	len = size_2d(kid->commands);
	tmp = (char **)malloc((len - my_doc->cut_len + 1) * sizeof(char *));
	if (!kid->commands)
		return ;
	make_kid_cmd(kid, tmp, len);
	free_double_array(kid->commands);
	kid->commands = tmp;
	return ;
}
