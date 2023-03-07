
#include "../minishell.h"

void	rm_node(t_env_list *top)
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

static int str_is_alpha(t_data *data, char *var)
{
	int i;

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
	if(data->args[1][0] == '\0')
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
			rm_node(tmp);
			env_list_to_matrix(data);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

int	is_builtin_last(t_data *data)
{
	int	last;

	if (data->pipe_count == 0)
		return (0);
	last = 0;
	while (data->args[last] != NULL)
		last++;
	last--;
	if (!ft_strcmp(data->args[last], "exit"))
		return (1);
	else if (!ft_strcmp(data->args[last], "cd"))
		ft_cd(data, NULL);
	else if (!ft_strcmp(data->args[last - 1], "cd"))
		ft_cd(data, data->args[last]);
	else if (!ft_strcmp(data->args[last], "unset"))
		return (1);
	return (0);
}

int	builtins(t_data *data)
{
	if (data->args == NULL)
		return (NO_CHILDS);
	if (count_pipes(data) == NO_CHILDS)
		return (NO_CHILDS);
	if (is_builtin_last(data) == 1)
		return (NO_CHILDS);
	if (data->pipe_count > 0)
		return (MAKE_CHILDS);
	else if (!ft_strcmp(data->args[0], "exit"))
		exit_function(data, "exit\n", 0);
	else if (!ft_strcmp(data->args[0], "cd"))
		ft_cd(data, data->args[1]);
	else if (!ft_strcmp(data->args[0], "export"))
		ft_export(data);
	else if (!ft_strcmp(data->args[0], "unset"))
		ft_unset(data);
	else
		return (MAKE_CHILDS);
	return (NO_CHILDS);
}
