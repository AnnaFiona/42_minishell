#include "minishell.h"

static void		syntax_error_func(t_data *data, t_child *kid, char *token)
{
	if (token == NULL)
	{
		if (data->pipe_count == 0 || data->pipe_count == kid->count)
			ft_printf("minishell: syntax error near token 'newline'\n");
		else
			ft_printf("minishell: syntax error near token '|'\n");
	}
	else
		ft_printf("minishell: syntax error near token '%s'\n", token);
	free_kid(kid);
	exit_function(data, NULL, 1);
	return ;
}

static void	is_it_a_token(t_data *data, t_child *kid, char **commands, int y)
{
	if (commands[y] == NULL)
		syntax_error_func(data, kid, commands[y]);
	if (commands[y][0] == '<')
		syntax_error_func(data, kid, commands[y]);
	if (commands[y][0] == '>')
		syntax_error_func(data, kid, commands[y]);
	return ;
}

static void	open_outfile(t_data *data, t_child *kid, char *file_name, int append)
{
	if (kid->outfile_fd != -1)
		close(kid->outfile_fd);
	if (append == 0)
		kid->outfile_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (append == 1)
		kid->outfile_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (kid->outfile_fd == -1)
	{
		ft_printf("could not open %s\n", file_name);
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	return ;
}

static void	cut_outfile(t_child *kid)
{
	char	**temp;
	int		len;
	int		y;

	y = 0;
	len = 0;
	while(kid->commands[len])
	{
		if (ft_strcmp(kid->commands[len], ">") == 0 || \
			ft_strcmp(kid->commands[len], ">>") == 0)
			break ;
		len++;
	}
	temp = malloc (sizeof(char *) * (len + 1));
	if (!temp)
		return ;//protection
	while (y < len)
	{
		temp[y] = ft_strdup(kid->commands[y]);
		y++;
	}
	temp[y] = NULL;
	free_double_array(kid->commands);
	kid->commands = temp;
	return ;
}

void	search_for_outfile(t_data *data, t_child *kid, char **commands)
{
	int	y;

	y = 0;
	while(commands[y])
	{
		if (ft_strcmp(commands[y], ">") == 0 && kid->in_quotes[y] != 'q')
		{
			is_it_a_token(data, kid, kid->commands, y + 1);
			open_outfile(data, kid, commands[y + 1], 0);
		}
		if (ft_strcmp(commands[y], ">>") == 0 && kid->in_quotes[y] != 'q')
		{
			is_it_a_token(data, kid, kid->commands, y + 1);
			open_outfile(data, kid, commands[y + 1], 1);
		}
		y++;
	}
	if (kid->outfile_fd != -1)
		cut_outfile(kid);
	return ;
}