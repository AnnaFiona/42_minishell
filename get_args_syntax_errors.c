#include "minishell.h"

static int    check_for_token(t_data *data, char *next_arg)
{
	int x;

	x = 0;
	if (next_arg == NULL)
	{
		ft_printf("+minishell: syntax error near unexpected token `newline'\n");
		data->exit_status = 2;
		return (1);
	}
	while(data->tokens[x])
	{
		if (ft_strcmp(next_arg, data->tokens[x]) == 0)
		{
			ft_printf("+minishell: syntax error near unexpected token `%s'\n", next_arg);
			data->exit_status = 2;
			return (1);
		}
		x++;
	}
	return (0);
}

void    search_syntax_errors(t_data *data)
{
	int y;
	int x;

	y = 0;
	while(data->args[y])
	{
		x = 0;
		while(data->tokens[x])
		{
			if (ft_strcmp(data->args[y], data->tokens[x]) == 0)
				if (check_for_token(data, data->args[y + 1]) == 1)
				{
					free_double_array(data->args);
					data->args = NULL;
					return ;
				}
			x++;
		}
		y++;
	}
	return ;
}