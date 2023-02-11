
#include "minishell.h"

static void	initialize_data(t_data *data)
{
	data->args = NULL;
	data->prompt = NULL;
	data->line = NULL;
	return ;
}

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	initialize_data(data);
	get_prompt(data);
	terminal_loop(data);
	exit_function(data, NULL, 0);
	return (0);
}