
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

int	builtins(t_data *data)
{
	if (data->args == NULL)
		return (NO_CHILDS);
	/* if (count_pipes(data) == NO_CHILDS)
		return (NO_CHILDS); */
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
