
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

static void	add_equal_to_list(t_data *data, char *var)
{
	t_env_list	*tmp;

	tmp = data->env_list;
	while (tmp != NULL)
	{
		if (!ft_strcmp(var, tmp->var))
		{
			tmp->equal = '=';
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

char	**ft_divide_at_char(char *args, char divider)
{
	int		i;
	int		len;
	char	**matrix;

	if (!args)
		return (NULL);
	i = 0;
	len = ft_strlen(args);
	while (args[i] && args[i] != divider)
		i++;
	if (args[i + 1] == '\0')
	{
		matrix = malloc(sizeof(char *) * 2);
		matrix[0] = ft_substr(args, 0, i);
		matrix[1] = NULL;
		return (matrix);
	}
	matrix = malloc(sizeof(char *) * 3);
	matrix[0] = ft_substr(args, 0, i);
	matrix[1] = ft_substr(args, i + 1, len);
	matrix[2] = NULL;
	return (matrix);
}

void	save_var(t_data *data, int i)
{
	char	**matrix;

	if (ft_strchr(data->args[i], '=') != NULL)
	{
		matrix = ft_divide_at_char(data->args[i], '=');
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
	int	i;

	if (!kid->commands[1])
		return ;
	i = 1;
	data->exit_status = 0;
	while (kid->commands[i])
	{
		if (ft_not_a_valid_char(data, kid->commands[i], "unset") == 0)
		{
			if (data->pipe_count == 0)
				save_var(data, i);
		}
		i++;
	}
	return ;
}
