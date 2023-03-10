
#include "../minishell.h"

static void	rm_node(t_env_list *top)
{
	t_env_list	*tmp;

	tmp = top->next;
	top->next = tmp->next;
	free(tmp->var);
	if (tmp->value != NULL)
		free(tmp->value);
	free(tmp);
	return ;
}

static int	str_is_alpha(t_data *data, char *var)
{
	int	i;

	i = 0;
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

void	ft_unset(t_data *data)
{
	t_env_list	*tmp;

	if (!data->args[1] || str_is_alpha(data, data->args[1]))
		return ;
	if (data->args[1][0] == '\0')
	{
		ft_printf("bash: unset: `': not a valid identifier\n");
		data->exit_status = 1;
		return ;
	}
	tmp = data->env_list;
	while (tmp->next != NULL)
	{
		if (!ft_strcmp(tmp->next->var, data->args[1]))
		{
			if (data->args[1][0] >= 'A' && data->args[1][0] <= 'Z')
				data->len_env--;
			save_path_in_data(data, tmp->next->value);
			rm_node(tmp);
			env_list_to_matrix(data);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}
