#include "minishell.h"

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
		return (-1);
	front = ft_substr(data->args[y], 0, x);
	back = ft_substr(data->args[y], x + 1, ft_strlen(data->args[y] + x));
	free(data->args[y]);
	data->args[y] = ft_strjoin(front, back);
	free(front);
	free(back);
	return (0);
}

static char	*variable_name(char *arg, int x)
{
	char	*var_name;
	int		len;

	x++;
	len = 0;
	if (arg[x] == '?')
		len = 2;
	else
	{
		while (arg[x + len])
		{
			if (ft_isalpha(arg[x + len]) == 0)
				break ;
			len++;
		}
	}
	var_name = ft_substr(arg, x, len);
	if (!var_name)
		return (NULL);
	return (var_name);
}

char	*strdup_or_strjoin(char const *s_1, char const *s_2)
{
	if (s_2 == NULL)
		return (ft_strdup(s_1));
	return (ft_strjoin(s_1, s_2));
}

static int	is_it_variable(t_data *data, int y, int x, char *tokens)
{
	int	i;

	i = 0;
	if (data->args[y][x] == '\0' || data->args[y][x] == ' ')
		return (1);
	while (tokens[i])
	{
		if (data->args[y][x] == tokens[i])
			return (1);
		i++;
	}
	return (0);
}

static void    actually_cut_arg(t_data *data, int to_cut, char **temp_arg, char *temp_quote)
{
	int len;
	int y;

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
	while(data->args[len])
		len++;
	temp_arg = malloc (sizeof(char *) * (len - 1));
	temp_quote = malloc (sizeof(char) * (len - 1));
	if (!temp_arg || !temp_quote)
		malloc_exit(data, NULL);
	actually_cut_arg(data, to_cut, temp_arg, temp_quote);
	free_double_array(data->args);
	data->args = temp_arg;
	free(data->in_quotes);
	data->in_quotes = temp_quote;
	return ;
}

int	replace_variables(t_data *data, int y, int x)
{
	char	*front_and_var;
	char	*variable;
	char	*var_name;
	char	*front;
	char	*back;

	if (is_it_variable(data, y, x + 1, "'\"|/") == 1)
		return (1);
	var_name = variable_name(data->args[y], x);
	if (data->args[y][x + 1] == '?')
		variable = ft_itoa(data->exit_status);
	else
		variable = ft_getenv(data, var_name);
	front = ft_substr(data->args[y], 0, x);
	back = ft_substr(data->args[y], x + ft_strlen(var_name) + 1, \
			ft_strlen(data->args[y] + x));
	free (data->args[y]);
	front_and_var = strdup_or_strjoin(front, variable);
	data->args[y] = strdup_or_strjoin(front_and_var, back);
	x = ft_strlen (front_and_var);
	free(front_and_var);
	free(variable);
	if (var_name != NULL)
		free(var_name);
	free(front);
	free(back);
	if (data->args[y][0] == '\0')
	{
		cut_arg(data, y);
		return (0);
	}
	return (x);
}
