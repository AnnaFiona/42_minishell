
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

static int	is_valid_unset(t_data *data, char *var, int x)
{
	int	i;

	i = 0;
	if (data->args[x][0] == '\0')
	{
		ft_printf("bash: unset: `': not a valid identifier\n");
		data->exit_status = 1;
		return (1);
	}
	while (var[i])
	{
		if (ft_isalpha(var[i]) == 0)
		{
			data->exit_status = 1;
			ft_printf("minishell: unset: `%s': not a valid identifier\n",
				var);
			return (1);
		}
		i++;
	}
	return (0);
}

static void ft_rm_var(t_data *data, int i)
{
	t_env_list	*tmp;

	tmp = data->env_list;
	while (tmp->next != NULL)
	{
		if (!ft_strcmp(tmp->next->var, data->args[i]))
		{
			if (data->args[i][0] >= 'A' && data->args[i][0] <= 'Z')
				data->len_env--;
			save_path_in_data(data, tmp->next->value);
			rm_node(tmp);
			env_list_to_matrix(data, 'x');
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_unset(t_data *data, t_child *kid)
{
	int i;

	i = 1;
	if (!kid->commands[1])
		return ;
	while(kid->commands[i])
	{
		is_valid_unset(data, kid->commands[i], i);
		if(data->pipe_count == 0)
			ft_rm_var(data, i);
		i++;
	}
	return ;
}
