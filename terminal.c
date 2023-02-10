
#include "minishell.h"

void	terminal_loop(t_data *data)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ctrl_c);
	/* signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, ctrl_d); */

	ft_printf("köfdhg");
	while (1)
	{
		data->line = readline(data->prompt);
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
