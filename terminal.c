
#include "minishell.h"

char	*rl_with_history(char *line, char *prompt)
{
	if (line)
	{
		free(line);
		line = (char *)NULL;
	}
	sig_controler(0);
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

void	terminal_loop(t_data *data)
{
	sig_controler(0);
	while (1)
	{

		if (!(data->line = rl_with_history(data->line, data->prompt)))
			ctrl_d_exit(data);
		split_line(data, data->line);
		if(builtins(data) == 1)
			redirect_children(data);
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
