#include "../minishell.h"

static void	open_outfile(t_data *data, t_child *kid, char *file_name,
		int append)
{
	if (kid->output_fd != -1)
		close(kid->output_fd);
	if (append == 0)
		kid->output_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (append == 1)
		kid->output_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (kid->output_fd == -1)
	{
		ft_printf("minishell: %s:", file_name);
		perror(" ");
		free_kid(kid);
		exit_function(data, NULL, 4);
	}
	return ;
}

static void	open_infile(t_data *data, t_child *kid, char *file_name)
{
	if (kid->input_fd != -1)
		close(kid->input_fd);
	kid->input_fd = open(file_name, O_RDONLY);
	if (kid->input_fd == -1)
	{
		ft_printf("minishell: %s:", file_name);
		perror(" ");
		free_kid(kid);
		exit_function(data, NULL, 3);
	}
	return ;
}

static int	in_or_out(t_data *data, t_child *kid, int y, int redirect)
{
	is_it_a_token(data, kid, kid->commands, y + 1);
	if (redirect == 0 || redirect == 1)
		open_outfile(data, kid, kid->commands[y + 1], redirect);
	else if (redirect == 2)
		open_infile(data, kid, kid->commands[y + 1]);
	cut_token(kid, y);
	return (-1);
}

void	search_for_arrows(t_data *data, t_child *kid)
{
	int	y;

	y = 0;
	while (kid->commands[y])
	{
		if (!ft_strcmp(kid->commands[y], ">") && kid->in_quotes[y] != 'q')
			y = in_or_out(data, kid, y, 0);
		else if (!ft_strcmp(kid->commands[y], ">>") && kid->in_quotes[y] != 'q')
			y = in_or_out(data, kid, y, 1);
		else if (!ft_strcmp(kid->commands[y], "<") && kid->in_quotes[y] != 'q')
			y = in_or_out(data, kid, y, 2);
		y++;
	}
	return ;
}
