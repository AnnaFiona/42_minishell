#include "../minishell.h"

void	ft_print_env(t_data *data)
{
	int	y;

	y = 0;
	while (data->env[y] != NULL)
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
	if (data->pipe_count > 0)
		return (MAKE_CHILDS);
	else
		return (MAKE_CHILDS);
	return (NO_CHILDS);
}

void	ft_dots(t_data *data, t_child *kid)
{
	char	*path_var;

	path_var = ft_getenv(data, "PATH");
	if (!ft_strcmp(kid->commands[0], ".."))
	{
		if (!path_var)
		{
			ft_printf("minishell: ..: Is a directory\n");
			data->exit_status = 1024;
		}
		else
		{
			ft_printf("..: command not found\n");
			data->exit_status = 768;
		}
	}
	else
	{
		ft_printf("minishell: .: filename argument required\n");
		ft_printf(".: usage: . filename [arguments]\n");
		data->exit_status = 512;
	}
	if (path_var)
		free(path_var);
	return ;
}

int	builtins_in_kid(t_data *data, t_child *kid)
{
	if (kid->no_fork == 1)
		return (NO_CHILDS);
	if (kid->commands == NULL || kid->commands[0] == NULL || \
		kid->commands[0][0] == '\0')
		return (MAKE_CHILDS);
	if (!ft_strcmp(kid->commands[0], "echo"))
		ft_echo(kid);
	else if (!ft_strcmp(kid->commands[0], "cd"))
		ft_cd(data, kid, kid->commands[1]);
	else if (!ft_strcmp(kid->commands[0], "pwd"))
		ft_printf("%s\n", data->saved_pwd);
	else if (!ft_strcmp(kid->commands[0], "exit"))
		end_minishell(data, kid);
	else if (!ft_strcmp(kid->commands[0], "..") || !ft_strcmp(kid->commands[0],
			"."))
		ft_dots(data, kid);
	else if (!ft_strcmp(kid->commands[0], "export") && kid->commands[1])
		ft_export(data, kid);
	else if (!ft_strcmp(kid->commands[0], "unset"))
		ft_unset(data, kid);
	else
		return (MAKE_CHILDS);
	return (NO_CHILDS);
}
