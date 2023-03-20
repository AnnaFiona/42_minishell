#include "minishell.h"

static int	ft_str_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_bigger_long_long(char *cmd, int is_negative)
{
	int		i;
	char	*max_longlong;

	i = 0;
	max_longlong = NULL;
	if (is_negative == 0)
		max_longlong = ft_strdup("9223372036854775808");
	else
		max_longlong = ft_strdup("9223372036854775807");
	while (cmd[i])
	{
		if (cmd[i] > max_longlong[i])
		{
			free(max_longlong);
			return (0);
		}
		i++;
	}
	free(max_longlong);
	return (1);
}

static int	is_valid_num(char *cmd)
{
	int	is_negative;

	is_negative = 1;
	if (cmd[0] == '-')
	{
		is_negative = 1;
		cmd++;
	}
	if (!ft_str_is_num(cmd))
		return (0);
	if (ft_strlen(cmd) < 19)
		return (1);
	if (ft_strlen(cmd) > 19)
		return (0);
	if (is_bigger_long_long(cmd, is_negative) == 0)
		return (0);
	return (1);
}

void	end_minishell(t_data *data, t_child *kid)
{
	int	exit;

	exit = 0;
	data->exit_status = 0;
	if (data->pipe_count == 0)
		ft_printf("exit\n");
	if (kid->commands[1])
	{
		if (!is_valid_num(kid->commands[1]))
		{
			ft_printf("bash: exit: %s: numeric argument required\n",
				kid->commands[1]);
			exit = 2;
		}
		else if (data->pipe_count == 0)
			exit = ft_atoi(kid->commands[1]);
	}
	if (data->pipe_count > 0)
		return ;
	if (exit < 0 || exit > 255)
		exit = exit % 256;
	ft_printf("%i", exit);
	free_kid(kid);
	exit_function(data, NULL, exit);
}
