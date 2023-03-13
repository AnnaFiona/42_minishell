#include "../minishell.h"

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
			if (ft_isalnum(arg[x + len]) == 0)
				break ;
			len++;
		}
	}
	var_name = ft_substr(arg, x, len);
	if (!var_name)
		return (NULL);
	return (var_name);
}

static int	is_it_variable(t_data *data, int y, int x, char *tokens)
{
	int	i;

	i = 0;
	if (y != 0 && ft_strcmp(data->args[y - 1], "<<") == 0)
		return (1);
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

static char	*get_front_and_var(t_data *data, char *var_name, int y, int x)
{
	char	*front_and_var;
	char	*variable;
	char	*front;

	if (data->args[y][x + 1] == '?')
		variable = ft_itoa(data->exit_status);
	else
		variable = ft_getenv(data, var_name);
	front = ft_substr(data->args[y], 0, x);
	front_and_var = strdup_or_strjoin(front, variable);
	free(variable);
	free(front);
	return (front_and_var);
}

int	replace_variables(t_data *data, int y, int x)
{
	char	*front_and_var;
	char	*var_name;
	char	*back;

	if (is_it_variable(data, y, x + 1, "'\"|/") == 1)
		return (x + 1);
	var_name = variable_name(data->args[y], x);
	front_and_var = get_front_and_var(data, var_name, y, x);
	back = ft_substr(data->args[y], x + ft_strlen(var_name) + 1, \
			ft_strlen(data->args[y] + x));
	free (data->args[y]);
	data->args[y] = strdup_or_strjoin(front_and_var, back);
	x = ft_strlen (front_and_var);
	free(front_and_var);
	if (var_name != NULL)
		free(var_name);
	free(back);
	if (data->args[y][0] == '\0')
	{
		cut_arg(data, y);
		return (0);
	}
	return (x);
}
