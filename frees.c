
#include "minishell.h"

void	free_double_array(char **arrarr)
{
	int	y;

	y = 0;
	if (arrarr == NULL)
		return ;
	while (arrarr[y])
	{
		free(arrarr[y]);
		y++;
	}
	free(arrarr);
}

void	free_kid(t_child *kid)
{
	if (kid->pid != NULL)
		free(kid->pid);
	if (kid->commands != NULL)
		free_double_array(kid->commands);
	if (kid->in_quotes != NULL)
		free(kid->in_quotes);
	if (kid->pipe_fd != NULL)
		free(kid->pipe_fd);
	if (kid->output_fd != -1)
		close (kid->output_fd);
	if (kid != NULL)
		free (kid);
}

void	free_data(t_data *data)
{
	if (data->tokens != NULL)
		free_double_array(data->tokens);
	if (data->saved_pwd != NULL)
		free(data->saved_pwd);
	if (data->args != NULL)
		free_double_array(data->args);
	if (data->path != NULL)
		free_double_array(data->path);
	if (data->env != NULL)
		free_double_array(data->env);
	if (data->in_quotes != NULL)
		free(data->in_quotes);
	if (data->prompt != NULL)
		free(data->prompt);
	if (data->line != NULL)
		free(data->line);
	if (data->env_list != NULL)
		free_env_list(&data->env_list);
	if (data != NULL)
		free(data);
	clear_history();
	return ;
}

void	exit_function(t_data *data, char *error_message, int error)
{
	if (error_message != NULL)
		ft_printf("%s", error_message);
	free_data(data);
	exit(error);
	return ;
}

void	ctrl_d_exit(t_data *data)
{
	write(1, "exit\n", 5);
	free_data(data);
	exit(0);
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