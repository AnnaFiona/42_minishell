
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
	return (0);
}

void	ft_print_env(t_data *data)
{
	int y;

	y = 0;
	while(data->env[y] != NULL)
	{
		if (ft_strchr(data->env[y], '=') != 0)
			ft_printf("%s\n", data->env[y]);
		y++;
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
	else
		return (MAKE_CHILDS);
	return (NO_CHILDS);
}

void	ft_dots(t_data *data, t_child *kid)
{
	char *path_var;

	path_var = ft_getenv(data, "PATH");
	if(!ft_strcmp(kid->commands[0], ".."))
	{
		if(path_var)
			ft_printf("minishell: ..: command not found\n");
		data->exit_status = 768;
	}
	else
	{
		ft_printf("minishell: .: filename argument required\n");
		ft_printf(".: usage: . filename [arguments]\n");
		data->exit_status = 512;
	}
	if(path_var)
		free(path_var);
	return ;
}

int	builtins_in_kid(t_data *data, t_child *kid)
{
	if (kid->commands == NULL || kid->commands[0][0] == '\0')
		return (MAKE_CHILDS);
	if (!ft_strcmp(kid->commands[0], "cd"))
		ft_cd(data, kid, kid->commands[1]);
	else if (!ft_strcmp(kid->commands[0], "..") || !ft_strcmp(kid->commands[0], "."))
		ft_dots(data, kid);
	else if (!ft_strcmp(kid->commands[0], "export"))
		ft_export(data, kid);
	else if (!ft_strcmp(kid->commands[0], "unset"))
		ft_unset(data);
	else 
		return (MAKE_CHILDS);
	return (NO_CHILDS);
}
