
#include "../minishell.h"

void	second_arg_null(t_data *data, int i)
{
	char	*value;

	value = NULL;
	if (!(is_dublicate(data, data->args[i], NULL)))
	{
		value = export_pwd_null(data, data->args[i]);
		add_list_end(data, data->env_list, ft_strdup(data->args[i]), value);
		env_list_to_matrix(data);
	}
	return ;
}

static void add_equal_to_list(t_data *data, char *var)
{
	t_env_list *tmp;

	tmp = data->env_list;
	while(tmp != NULL)
	{
		if(!ft_strcmp(var, tmp->var))
		{
			tmp->equal = '=';
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	save_var(t_data *data, int i)
{
	char	**matrix;

	if (ft_strchr(data->args[i], '=') != NULL)
	{
		matrix = ft_split(data->args[i], '=');
		if (!is_dublicate(data, matrix[0], matrix[1]))
		{
			add_list_end(data, data->env_list, ft_strdup(matrix[0]),
				ft_strdup(matrix[1]));
		}
		if (ft_strchr(data->args[i], '=') && !matrix[1])
			add_equal_to_list(data, matrix[0]);
		env_list_to_matrix(data);
		free_double_array(matrix);
		return ;
	}
	second_arg_null(data, i);
	return ;
}

void	ft_export(t_data *data, t_child *kid)
{
	int i;

	if (!kid->commands[1])
		return ;
	i = 1;
	data->exit_status = 0;
	while(kid->commands[i])
	{
		if(ft_not_a_valid_char(data, kid->commands[i], "unset") == 0)
		{
			if(data->pipe_count == 0)
				save_var(data, i);
		}
		i++;
	}
	return ;
}
