
#include "../minishell.h"

void	save_path_in_data(t_data *data, char *value)
{
	if (!ft_strcmp(data->args[1], "PWD"))
	{
		if (data->saved_pwd)
			return ;
		data->saved_pwd = ft_strdup(value);
	}
	return ;
}

static void	ft_is_equal(t_data *data, char *var, char equalsign, int y)
{
	if (equalsign == '=')
		data->env[y] = ft_strjoin(var, "=");
	else
		data->env[y] = ft_strdup(var);
	return ;
}

void	env_list_to_matrix(t_data *data)
{
	int			y;
	char		*line;
	t_env_list	*tmp;

	y = 0;
	tmp = data->env_list;
	free_double_array(data->env);
	data->env = malloc(sizeof(char *) * (size_of_list(tmp) + 1));
	if (!data->env)
		malloc_exit(data, NULL);
	while (tmp != NULL)
	{
		if (tmp->value == NULL)
			ft_is_equal(data, tmp->var, tmp->equal, y);
		else
		{
			line = ft_strjoin(tmp->var, "=");
			data->env[y] = ft_strjoin(line, tmp->value);
			free(line);
		}
		tmp = tmp->next;
		y++;
	}
	data->env[y] = NULL;
	return ;
}
