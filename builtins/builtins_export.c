
#include "../minishell.h"

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

int		is_valid_var(char *var)
{
	int i;

	i = 0;
	if(var[i] >= 'A' && var[i] <= 'Z')
		return (1);
	while(var[i])
	{
		if(!ft_isalpha(var[i]))
			return (1);
		i++;
	}
	return(0);
}

void second_arg_null(t_data *data)
{
	if(is_dub_in_ori(data, data->args[1], NULL) && is_valid_var(data->args[1]))
		return;
	if(!(is_dublicate(data, data->args[1], NULL)))
	{
		add_list_end(data, data->env_list, ft_strdup(data->args[1]), NULL);
		env_list_to_matrix(data);
	}
	return ;
}


void	save_var(t_data *data)
{
	char	**matrix;

	if (ft_strchr(data->args[1], '=') != NULL)
	{
		matrix = ft_split(data->args[1], '=');
		if(is_dub_in_ori(data, matrix[0], matrix[1]) && is_valid_var(data->args[1]))
		{
			free_double_array(matrix);
			return ;
		}
		if(!is_dublicate(data, matrix[0], matrix[1]))
		{
			add_list_end(data, data->env_list, ft_strdup(matrix[0]),
				ft_strdup(matrix[1]));
		}
		env_list_to_matrix(data);
		free_double_array(matrix);
		return ;
	}
	second_arg_null(data);
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
