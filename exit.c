#include "minishell.h"

static int	ft_str_is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_function(t_data *data, char *error_message, int error)
{
	if (error_message != NULL)
		ft_printf("%s", error_message);
	free_data(data);
	exit(error);
	return ;
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
		if (ft_strlen(kid->commands[1]) > 19
			|| !ft_str_is_num(kid->commands[1]))
			ft_printf("bash: exit: %s: numeric argument required\n",
				kid->commands[1]);
		else if (ft_strlen(kid->commands[1]) < 4)
			exit = atoi(kid->commands[1]);
	}
	if (data->pipe_count > 0)
		return ;
	if (exit < 0)
		exit = 0;
	else if (exit > 255)
		exit = 255;
	free_kid(kid);
	exit_function(data, NULL, exit);
}

void	malloc_exit(t_data *data, t_child *kid)
{
	write(2, "malloc failed\n", 14);
	if (data != NULL)
		free_data(data);
	if (kid != NULL)
		free_kid(kid);
	exit(12);
}

void	ctrl_d_exit(t_data *data)
{
	write(1, "exit\n", 5);
	free_data(data);
	exit(0);
}
