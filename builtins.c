
#include "minishell.h"

void	ft_cd(t_data *data)
{
	if (data->args[1] == NULL)
		chdir(getenv("HOME"));
	else if (chdir(data->args[1]))
		perror("Error ");
	return ;
}

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

void	ft_unset(t_data *data)
{
	t_env_list	*tmp;

	if (!data->args[1] || ft_strchr(data->args[1], '='))
		return ;
	tmp = data->env_list;
	while (tmp->next != NULL)
	{
		if (!ft_strcmp(tmp->next->var, data->args[1]))
		{
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
		return (1);
	else if (!ft_strcmp(data->args[last], "unset"))
		return (1);
	return (0);
}

int	builtins(t_data *data)
{
	if (data->args == NULL)
		return (0);
	count_pipes(data);
	if (is_builtin_last(data) == 1)
		return (0);
	if (data->pipe_count > 0)
		return (1);
	else if (!ft_strcmp(data->args[0], "exit"))
		exit_function(data, "exit\n", 0);
	else if (!ft_strcmp(data->args[0], "cd"))
		ft_cd(data);
	else if (!ft_strcmp(data->args[0], "export"))
		ft_export(data);
	else if (!ft_strcmp(data->args[0], "unset"))
		ft_unset(data);
	else
		return (1);
	return (0);
}
