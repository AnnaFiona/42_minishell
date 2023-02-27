#include "../minishell.h"

static void		syntax_error_func(t_data *data, t_child *kid, char *token)
{
	if (token == NULL)
	{
		if (data->pipe_count == 0 || data->pipe_count == kid->count)
			ft_printf("minishell: syntax error near unexpected token 'newline'\n");
		else
			ft_printf("minishell: syntax error near unexpected token '|'\n");
	}
	else
	{
		print_double_array(kid->commands);	
		ft_printf("minishell: syntax error near unexpected token '%s'\n", token);
	}
	free_kid(kid);
	exit_function(data, NULL, 1);
	return ;
}

void	is_it_a_token(t_data *data, t_child *kid, char **commands, int y)
{
	if (commands[y] == NULL)
		syntax_error_func(data, kid, commands[y]);
	if (commands[y][0] == '<' && kid->in_quotes[y] != 'q')
		syntax_error_func(data, kid, commands[y]);
	if (commands[y][0] == '>' && kid->in_quotes[y] != 'q')
		syntax_error_func(data, kid, commands[y]);
	return ;
}

static void    actually_cut_token(t_child *kid, int to_cut, char **temp_com, char *temp_quote)
{
	int len;
	int y;

	y = 0;
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
	return ;
}

void	cut_token(t_child *kid, int to_cut)
{
	char	**temp_com;
	char	*temp_quote;
	int		len;

	len = 0;
	while(kid->commands[len])
		len++;
	temp_com = malloc (sizeof(char *) * (len - 1));
	temp_quote = malloc (sizeof(char) * (len - 1));
	if (!temp_com || !temp_quote)
		return ;//protection
	actually_cut_token(kid, to_cut, temp_com, temp_quote);
	free_double_array(kid->commands);
	kid->commands = temp_com;
	free(kid->in_quotes);
	kid->in_quotes = temp_quote;
	return ;
}
