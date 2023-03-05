
#include "../minishell.h"

void	env_list_to_matrix(t_data *data)
{
	int			y;
	char		*line;
	t_env_list	*tmp;

	y = 0;
	tmp = data->env_list;
	free_double_array(data->env);
	data->env = malloc(sizeof(char *) * (size_of_list(tmp) + 1));
	while (tmp != NULL)
	{
		if (tmp->value == NULL)
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

int ft_len_to_char(char *str, char c)
{
	int i;

	i = 0;
	while(str[i])
	{
		i++;
		if(str[i] == c)
			break;
	}
	return (i);
}

int is_already_there(t_data *data, char *var)
{
	int i;
	int len;

	i = 0;
	while(data->env[i])
	{
		len = ft_len_to_char(data->env[i], '=');
		if(!ft_strncmp(var, data->env[i], len))
			return (0);
		i++;
	}
	return (1);
}

int is_in_ori_env(t_data *data, char *var)
{
	int i;
	int len;
	int	ok;

	i = 0;
	ok = -1;
	if (var[i] < 'A' && var[i] > 'Z')
		return (1);
	while(data->env_ori[i])
	{
		len = ft_len_to_char(data->env_ori[i], '=');
		if(!ft_strncmp(var, data->env_ori[i], len))
		{
			if(is_already_there(data, var) == 1)
				data->len_env++;
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_valid_var(t_data *data, char *var)
{
	int	i;

	i = 0;
	if(is_in_ori_env(data, var) == 1)
		return(1);
	/* if (var[i] >= 'A' && var[i] <= 'Z')
		return (1); */
	while (var[i])
	{
		if (ft_isalpha(var[i]) == 0)
		{
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
	if (is_dub_in_ori(data, data->args[1], NULL) || is_valid_var(data,
			data->args[1]))
		return ;
	if (!(is_dublicate(data, data->args[1], NULL)))
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
