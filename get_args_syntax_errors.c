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
	while(data->tokens_heredoc[x])
	{
		if (ft_strcmp(next_arg, data->tokens_heredoc[x]) == 0)
		{
			ft_printf("+minishell: syntax error near unexpected token `%s'\n", next_arg);
			data->exit_status = 2;
			return (1);
		}
		x++;
	}
	return (0);
}

static int check_pipes(t_data *data)
{
	int y;

	y = 0;
	while(data->args[y])
	{
		if (ft_strcmp(data->args[y], "|") == 0)
		{
			if (y == 0 || ft_strcmp(data->args[y + 1], "|") == 0)
			{
				ft_printf("-minishell: syntax error near unexpected token `|'\n");
				data->exit_status = 2;
				return (1);
			}
			else if (data->args[y + 1] == NULL)
			{
				ft_printf("-minishell: syntax error near unexpected token `newline'\n");
				data->exit_status = 2;
				return (1);
			}
		}
		y++;
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
	if (check_pipes(data) == 1)
	{
		free_double_array(data->args);
		data->args = NULL;
		return ;
	}
	return ;
}