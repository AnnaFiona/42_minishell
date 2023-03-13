#include "../minishell.h"

static int	set_data_quote(t_data *data, char *arg, char quote, int x)
{
	if (data->quote == '\0' && find_second_quote(arg, quote, x) == -1)
		return (-1);
	if (data->quote == '\0')
		data->quote = quote;
	else if (data->quote == '\'')
		data->quote = '\0';
	else if (data->quote == '"')
		data->quote = '\0';
	return (0);
}

int	cut_quotes(t_data *data, int y, int x)
{
	char	*front;
	char	*back;

	if (set_data_quote(data, data->args[y], data->args[y][x], x) == -1)
		return (0);
	front = ft_substr(data->args[y], 0, x);
	back = ft_substr(data->args[y], x + 1, ft_strlen(data->args[y] + x));
	free(data->args[y]);
	data->args[y] = ft_strjoin(front, back);
	free(front);
	free(back);
	return (-1);
}

char	*strdup_or_strjoin(char const *s_1, char const *s_2)
{
	if (s_2 == NULL)
		return (ft_strdup(s_1));
	return (ft_strjoin(s_1, s_2));
}
