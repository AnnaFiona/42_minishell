
#include "minishell.h"

void	add_env(t_data *data, char *str)
{
	int len;
	//char **new_env;

	if(!str)
		return ;
	len = size_2d(data->env);
	data->env[len] = ft_strdup(str);
	data->env[++len] = NULL;
	return ;
}

void	save_var(t_data *data)
{
	char	**matrix;
	char	*line;
	char 	*final;

	if (ft_strchr(data->args[1], '=') != NULL)
	{
		matrix = ft_split(data->args[1], '=');
		line = ft_strjoin("\"", matrix[1]);
		line = ft_strjoin(line, "\"");
		final = ft_strjoin(data->args[0], "=");
		final = ft_strjoin(final, line);
		add_env(data, final);
		free_double_array(matrix);
		free(final);
		free(line);
		return ;
	}
	add_env(data, data->args[1]);
	return ;
}

void	ft_export(t_data *data)
{
	if (data->args[1] == NULL)
		sort_env(data, data->env);
	else if (data->args[1])
		save_var(data);
	return ;
}
