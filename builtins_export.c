
#include "minishell.h"

void	env_list_to_matrix(t_data *data)
{
	int y;
	char *line;
	t_env_list *tmp;

	y = 0;
	tmp = data->env_list;
	free_double_array(data->env);
	data->env = malloc(sizeof(char *) * (size_of_list(tmp) + 1));
	while(tmp != NULL)
	{
		if(tmp->value == NULL)
			data->env[y] = ft_strdup(tmp->var);
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

int	is_dublicate(t_data *data, char *var, char *value)
{
	t_env_list	*tmp;

	tmp = data->env_list;
	while (tmp != NULL)
	{
		if (ft_strcmp(var, tmp->var) == 0)
		{
			if(value != NULL)
			{
				free(tmp->value);
				tmp->value = value;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	save_var(t_data *data)
{
	char	**matrix;

	if (ft_strchr(data->args[1], '=') != NULL)
	{
		matrix = ft_split(data->args[1], '=');
		if(!is_dublicate(data, ft_strdup(matrix[0]), ft_strdup(matrix[1])))
		{
			add_list_end(data, data->env_list, ft_strdup(matrix[0]),
				ft_strdup(matrix[1]));
		}
		free_double_array(matrix);
	}
	else if(!(is_dublicate(data, ft_strdup(data->args[1]), NULL)))
		add_list_end(data, data->env_list, ft_strdup(data->args[1]), NULL);
	env_list_to_matrix(data);
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
