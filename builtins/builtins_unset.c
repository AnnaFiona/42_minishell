
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

int	ft_not_a_valid_char(t_data *data, char *var, char *ex_or_un)
{
	int	i;

	i = 0;
	if (var[0] == '\0')
	{
		ft_printf("minishell: %s: `': not a valid identifier\n", ex_or_un);
		data->exit_status = 1;
		return (1);
	}
	while (var[i] && var[i] != '=')
	{
		if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		{
			data->exit_status = 1;
			ft_printf("minishell: %s: `%s': not a valid identifier\n",
				ex_or_un, var);
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
			/* if (data->args[i][0] >= 'A' && data->args[i][0] <= 'Z')
				data->len_env--; */
			save_path_in_data(data, tmp->next->value);
			rm_node(tmp);
			env_list_to_matrix(data);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_unset(t_data *data, t_child *kid)
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
				ft_rm_var(data, i);
		}
		i++;
	}
	return ;
}
