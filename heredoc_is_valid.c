
#include "minishell.h"

void	free_doc(t_child *kid, t_here *doc)
{
	free_kid(kid);
	if(doc->line)
		free(doc->line);
	if(doc->order)
		free_double_array(doc->order);
	free(doc);
	exit(0);
}

int	is_valid_heredoc(t_child *kid, t_here *doc)
{
	int i;
	int	len;

	i = 0;
	if (!kid->commands)
		return (-1);
	len = 0;
	if (!kid->commands[1])
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	while (kid->commands[i])
	{
		if(!ft_strcmp(kid->commands[i], "<<") && !ft_strcmp(kid->commands[i + 1], "<<"))
		{
			kid->guard_fork = 1;
			ft_printf("bash: syntax error near unexpected token `<<'\n");
			if(len == 0)
				return (-1);
			doc->range = i - 1;
			return (len);
		}
		if(!ft_strcmp(kid->commands[i], "<<") && !kid->commands[i + 1])
			return (-1);
		if(!ft_strcmp(kid->commands[i], "<<"))
			len++;
		i++;
	}
	if (!kid->commands[len])
		return (-1);
	doc->range = size_2d(kid->commands);
	return (len);
}