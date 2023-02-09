
#include "minishell.h"

void	free_data(t_data *data)
{
	free(data->prompt);
	free(data->line);
	free(data);
	return ;
}

void    exit_function(t_data *data, char *error_message, int error)
{
	///
	free_data(data);
	if (error != 0)
		ft_printf("%s", error_message);
	exit(error);
	return ;
}
