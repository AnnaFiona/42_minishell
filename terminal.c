
#include "minishell.h"

void	terminal_loop(t_data *data)
{
	sig_controler(0);
	while (1)
	{
		if (!(data->line = readline(data->prompt)))
			ctrl_d_exit(data);
		split_line(data, data->line);
		free_double_array(data->args);
		data->args = NULL;
	}
	return ;
}

void	get_prompt(t_data *data)
{
	char	*temp_user;

	temp_user = getenv("USER");
	if (!temp_user)
		exit_function(data, "Error:\n	No user found\n", 1);
	data->prompt = ft_strjoin(temp_user, ": ");
	return ;
}
