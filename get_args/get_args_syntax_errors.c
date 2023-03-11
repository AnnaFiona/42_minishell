#include "../minishell.h"

static void	print_syntax_error(t_data *data, int error, char *next_arg)
{
	if (error == 1)
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
	else if (error == 2)
	{
		ft_printf("minishell: syntax error near ");
		ft_printf("unexpected token `%s'\n", next_arg);
	}
	else if (error == 3)
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	data->guard_fork = 1;
	return ;
}

static int	check_for_token(t_data *data, char *next_arg)
{
	int	x;

	x = 0;
	if (next_arg == NULL)
	{
		print_syntax_error(data, 1, NULL);
		return (1);
	}
	while (data->tokens_pipe[x])
	{
		if (ft_strcmp(next_arg, data->tokens_pipe[x]) == 0)
		{
			print_syntax_error(data, 2, next_arg);
			return (1);
		}
		x++;
	}
	return (0);
}

int	check_pipes(t_data *data)
{
	int	y;

	y = 0;
	while (data->args[y])
	{
		if (ft_strcmp(data->args[y], "|") == 0)
		{
			if (y == 0 || ft_strcmp(data->args[y + 1], "|") == 0)
			{
				print_syntax_error(data, 3, NULL);
				return (1);
			}
			else if (data->args[y + 1] == NULL)
			{
				print_syntax_error(data, 1, NULL);
				return (1);
			}
		}
		y++;
	}
	return (0);
}

void	search_syntax_errors(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->args[y])
	{
		x = 0;
		while (data->tokens[x])
		{
			if (ft_strcmp(data->args[y], data->tokens[x]) == 0)
			{
				if (check_for_token(data, data->args[y + 1]) == 1)
				{
					data->guard_fork = 1;
					return ;
				}
			}
			x++;
		}
		y++;
	}
	check_pipes(data);
	return ;
}
