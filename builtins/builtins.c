
#include "../minishell.h"

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

void	ft_print_env(t_data *data)
{
	t_env_list	*temp;

	temp = data->env_list;
	while(temp != NULL)
	{
		if (temp->value != NULL)
			ft_printf("%s=%s\n", temp->var, temp->value);
		temp = temp->next;
	}
	return ;
}

int	builtins(t_data *data)
{
	if (data->args == NULL)
		return (NO_CHILDS);
	if (is_builtin_last(data) == 1)
		return (NO_CHILDS);
	if (data->pipe_count > 0)
		return (MAKE_CHILDS);
	else if (!ft_strcmp(data->args[0], "exit"))
		exit_function(data, "exit\n", 0);
	else if (!ft_strcmp(data->args[0], "cd"))
		ft_cd(data, data->args[1]);
	/* else if (!ft_strcmp(data->args[0], "export"))
		ft_export(data); */
	/* else if (!ft_strcmp(data->args[0], "unset"))
		ft_unset(data); */
	/* else if (!ft_strcmp(data->args[0], "env"))
		ft_print_env(data); */
	else
		return (MAKE_CHILDS);
	return (NO_CHILDS);
}

int	builtins_in_kid(t_data *data, t_child *kid)
{
	if (kid->commands == NULL || kid->commands[0][0] == '\0')
		return (MAKE_CHILDS);
	/* if(ft_strcmp(data->args[0], "unset") || ft_strcmp(kid->commands[0], "export"))
		return (MAKE_CHILDS); */
	/* if (is_builtin_last(data) == 1)
		return (NO_CHILDS); */
	/* else if (!ft_strcmp(data->args[0], "exit"))
		exit_function(data, "exit\n", 0); */
/* 	if (!ft_strcmp(data->args[0], "cd"))
		ft_cd(data, data->args[1]); */
	if (!ft_strcmp(kid->commands[0], "export"))
		ft_export(data, kid);
	else if (!ft_strcmp(kid->commands[0], "unset"))
		ft_unset(data);
	else 
		return (MAKE_CHILDS);
	return (NO_CHILDS);
}
