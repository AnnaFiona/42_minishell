#include "../minishell.h"

static void	actually_cut_token(t_child *kid, int to_cut, char **temp_com,
		char *temp_quote)
{
	int	len;
	int	y;

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
	while (kid->commands[len])
		len++;
	temp_com = malloc(sizeof(char *) * (len - 1));
	if (!temp_com)
		malloc_exit(NULL, kid);
	temp_quote = malloc(sizeof(char) * (len - 1));
	if (!temp_quote)
		malloc_exit(NULL, kid);
	if (!temp_com || !temp_quote)
		return ;
	actually_cut_token(kid, to_cut, temp_com, temp_quote);
	free_double_array(kid->commands);
	kid->commands = temp_com;
	free(kid->in_quotes);
	kid->in_quotes = temp_quote;
	return ;
}
