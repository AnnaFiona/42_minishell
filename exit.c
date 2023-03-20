#include "minishell.h"

void	exit_function(t_data *data, char *error_message, int error)
{
	if (error_message != NULL)
		ft_printf("%s", error_message);
	free_data(data);
	exit(error);
	return ;
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
