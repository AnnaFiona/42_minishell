
#include "../minishell.h"

void	env_list_to_matrix(t_data *data, char equalsign)
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
		{
			if (equalsign == '=')
				data->env[y] = ft_strjoin(tmp->var, "=");
			else
				data->env[y] = ft_strdup(tmp->var);
		}
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

int	is_valid_var(t_data *data, char *var)
{
	int	i;

	i = 0;
	if(is_in_ori_env(data, var) == 1)
		return(1);
	while (var[i])
	{
		if (ft_isalpha(var[i]) == 0)
		{
			data->exit_status = 1;
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				data->args[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	second_arg_null(t_data *data)
{
	char *value;

	value = NULL;
	if (is_dub_in_ori(data, data->args[1], NULL) || is_valid_var(data,
			data->args[1]))
		return ;
	if (!(is_dublicate(data, data->args[1], NULL)))
	{
		value = export_pwd_null(data, data->args[1]);
		add_list_end(data, data->env_list, ft_strdup(data->args[1]), value);
		env_list_to_matrix(data, 'x');
	}
	return ;
}

void	save_var(t_data *data)
{
	char	**matrix;

	if (ft_strchr(data->args[1], '=') != NULL)
	{
		matrix = ft_split(data->args[1], '=');
		if (is_dub_in_ori(data, matrix[0], matrix[1]) || is_valid_var(data,
				matrix[0]))
		{
			free_double_array(matrix);
			return ;
		}
		if (!is_dublicate(data, matrix[0], matrix[1]))
		{
			add_list_end(data, data->env_list, ft_strdup(matrix[0]),
				ft_strdup(matrix[1]));
		}
		env_list_to_matrix(data, '=');
		free_double_array(matrix);
		return ;
	}
	second_arg_null(data);
	return ;
}

void	ft_export(t_data *data)
{
	if (data->args[1] == NULL)
	{
		data->exit_status = 0;
		sort_env(data, data->env);
	}
	else if (data->args[1])
	{
		data->exit_status = 0;
		if(data->args[1][0] == '\0')
		{
			data->exit_status = 1;
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				data->args[1]);
			return ;
		}
		save_var(data);
	}
	return ;
}
