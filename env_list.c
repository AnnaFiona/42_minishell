#include "minishell.h"

void	create_env_list(t_data *data, t_env_list **top, char *var, char *value)
{
	if (*top)
		return ;
	*top = (t_env_list *)malloc(sizeof(t_env_list));
	if (!*top)
		malloc_exit(data, NULL);
	(*top)->var = var;
	(*top)->value = value;
	(*top)->next = NULL;
	return ;
}

void	add_list_end(t_data *data, char *var, char *value, char sign)
{
	t_env_list	*tmp;

	tmp = data->env_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_env_list *)malloc(sizeof(t_env_list));
	if (!tmp->next)
		malloc_exit(data, NULL);
	tmp->next->var = var;
	tmp->next->equal = sign;
	tmp->next->value = value;
	tmp->next->next = NULL;
	return ;
}

void	matrix_to_list(t_data *data, char **env)
{
	char	**matrix;
	int		y;

	y = 1;
	if (data->env_list)
		free_env_list(&data->env_list);
	matrix = ft_divide_at_char(data, env[0], '=');
	create_env_list(data, &data->env_list, ft_strdup(matrix[0]),
		ft_strdup(matrix[1]));
	free_double_array(matrix);
	while (env[y])
	{
		if (ft_strchr(env[y], '='))
		{
			matrix = ft_divide_at_char(data, env[y], '=');
			add_list_end(data, ft_strdup(matrix[0]), ft_strdup(matrix[1]), '=');
			free_double_array(matrix);
		}
		else
			add_list_end(data, ft_strdup(env[y]), NULL, '-');
		y++;
	}
	return ;
}
