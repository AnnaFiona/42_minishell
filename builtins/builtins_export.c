
#include "../minishell.h"

int	is_valid_var(t_data *data, char *var, int x)
{
	int	i;

	i = 0;
	if (is_in_ori_env(data, var) == 1)
		return (1);
	while (var[i])
	{
		if (ft_isalpha(var[i]) == 0)
		{
			data->exit_status = 1;
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				data->args[x]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	second_arg_null(t_data *data, int i)
{
	char	*value;

	value = NULL;
	if (is_dub_in_ori(data, data->args[i], NULL) || is_valid_var(data,
			data->args[i], i))
		return ;
	if (!(is_dublicate(data, data->args[i], NULL)))
	{
		value = export_pwd_null(data, data->args[i]);
		add_list_end(data, data->env_list, ft_strdup(data->args[i]), value);
		env_list_to_matrix(data, 'x');
	}
	return ;
}

void	save_var(t_data *data, int i)
{
	char	**matrix;

	if (ft_strchr(data->args[i], '=') != NULL)
	{
		matrix = ft_split(data->args[i], '=');
		if (is_dub_in_ori(data, matrix[0], matrix[1]) || is_valid_var(data,
				matrix[0], i))
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
	second_arg_null(data, i);
	return ;
}

void	ft_export(t_data *data, t_child *kid)
{
	int i;

	(void)kid;
	i = 1;
	if (!ft_strcmp(data->args[0], "export") && data->args[1]
		&& data->pipe_count == 0)
	{
		data->exit_status = 0;
		while(data->args[i])
		{
			if (data->args[i][0] == '\0')
			{
				data->exit_status = 1;
				ft_printf("minishell: export: `%s': not a valid identifier\n",
					data->args[i]);
			}
			else
				save_var(data, i);
			i++;
		}
	}
	return ;
}
