#include "minishell.h"

static void	renew_data(t_data *data)
{
	if (data->args != NULL)
	{
		free_double_array(data->args);
		data->args = NULL;
	}
	if (data->in_quotes != NULL)
	{
		free(data->in_quotes);
		data->in_quotes = NULL;
	}
	data->args_y = 0;
	return ;
}

static char	*rl_with_history(char *line, char *prompt)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

void	terminal_loop(t_data *data)
{
	while (1)
	{
		data->line = rl_with_history(data->line, data->prompt);
		if (data->line == NULL)
			ctrl_d_exit(data);
		get_args(data, data->line);
		if (builtins(data) == 1)
			redirect_children(data);
		renew_data(data);
	}
	return ;
}

void	get_prompt(t_data *data)
{
	char	*temp_user;

	temp_user = getenv("USER");
	if (!temp_user)
		data->prompt = ft_strdup("\033[0;31mredacted: \033[0m");
	else
		data->prompt = ft_strjoin(temp_user, ": ");
	return ;
}
