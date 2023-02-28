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

int	replace_variables(t_data *data, int y, int x)
{
	char	*front_and_var;
	char	*variable;
	char	*var_name;
	char	*front;
	char	*back;

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
	return (x);
}
