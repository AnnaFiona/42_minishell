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
	if (commands[y][0] == '<' && kid->in_quotes[y] != 'q')
		syntax_error_func(data, kid, commands[y]);
	if (commands[y][0] == '>' && kid->in_quotes[y] != 'q')
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

void	cut_token(t_child *kid, int to_cut)
{
	char	**temp_com;
	char	*temp_quote;
	int		len;
	int		y;

	len = 0;
	y = 0;
	while(kid->commands[len])
		len++;
	temp_com = malloc (sizeof(char *) * (len - 1));
	temp_quote = malloc (sizeof(char) * (len - 1));
	if (!temp_com || !temp_quote)
		return ;//protection
	len = 0;
	while (kid->commands[len])
	{
		if (len != to_cut && len != to_cut + 1)
		{
			temp_com[y] = ft_strdup(kid->commands[len]);
			temp_quote[y] = kid->in_quotes[len];
			y++;
		}
		len++;
	}
	temp_com[y] = NULL;
	temp_quote[y] = '\0';
	free_double_array(kid->commands);
	kid->commands = temp_com;
	free(kid->in_quotes);
	kid->in_quotes = temp_quote;
	return ;
}

void	search_for_outfile(t_data *data, t_child *kid)
{
	int	y;

	y = 0;
	while(kid->commands[y])
	{
		if (ft_strcmp(kid->commands[y], ">") == 0 && kid->in_quotes[y] != 'q')
		{
			is_it_a_token(data, kid, kid->commands, y + 1);
			open_outfile(data, kid, kid->commands[y + 1], 0);
			cut_token(kid, y);
			y--;
		}
		if (ft_strcmp(kid->commands[y], ">>") == 0 && kid->in_quotes[y] != 'q')
		{
			is_it_a_token(data, kid, kid->commands, y + 1);
			open_outfile(data, kid, kid->commands[y + 1], 1);
			cut_token(kid, y);
			y--;
		}
		y++;
	}
	return ;
}