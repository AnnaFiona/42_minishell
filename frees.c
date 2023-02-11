
#include "minishell.h"

void	free_double_array(char **arrarr)
{
	int	y;

	y = 0;
	while (arrarr[y])
	{
		free(arrarr[y]);
		y++;
	}
	free(arrarr);
}

void	free_data(t_data *data)
{
	if (data->args != NULL)
		free_double_array(data->args);
	if (data->prompt != NULL)
		free(data->prompt);
	if (data->line != NULL)
		free(data->line);
	if (data != NULL)
		free(data);
	return ;
}

void    exit_function(t_data *data, char *error_message, int error)
{
	free_data(data);
	if (error != 0)
		ft_printf("%s", error_message);
	exit(error);
	return ;
}
