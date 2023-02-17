
#include "minishell.h"

static void	initialize_data(t_data *data)
{
	data->env_list = NULL;
	data->args = NULL;
	data->prompt = NULL;
	data->line = NULL;
	data->path = NULL;
	data->env = NULL;
	data->pipe_count = -1;
	data->args_y = -1;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data *data;

	(void) argc;
	(void) argv;
	data = malloc(sizeof(t_data));
	initialize_data(data);
	get_prompt(data);
	envp_to_path(data, envp);
	matrix_to_list(data, data->env, &data->env_list);
	terminal_loop(data);
	exit_function(data, NULL, 0);
	return (0);
}

void	print_double_array(char **arrarr)
{
	int	y;

	y = 0;
	if (arrarr == NULL)
		return ;
	while (arrarr[y])
	{
		ft_printf("%s\n", arrarr[y]);
		y++;
	}
}