#include "../minishell.h"

static void	actually_cut_arg(t_data *data, int to_cut, \
							char **temp_arg, char *temp_quote)
{
	int	len;
	int	y;

	y = 0;
	len = 0;
	while (data->args[len])
	{
		if (len != to_cut)
		{
			temp_arg[y] = ft_strdup(data->args[len]);
			temp_quote[y] = data->in_quotes[len];
			y++;
		}
		len++;
	}
	temp_arg[y] = NULL;
	temp_quote[y] = '\0';
	return ;
}

void	cut_arg(t_data *data, int to_cut)
{
	char	**temp_arg;
	char	*temp_quote;
	int		len;

	len = 0;
	while (data->args[len])
		len++;
	temp_arg = malloc (sizeof(char *) * (len));
	temp_quote = malloc (sizeof(char) * (len));
	if (!temp_arg || !temp_quote)
		malloc_exit(data, NULL);
	actually_cut_arg(data, to_cut, temp_arg, temp_quote);
	free_double_array(data->args);
	data->args = temp_arg;
	free(data->in_quotes);
	data->in_quotes = temp_quote;
	return ;
}
