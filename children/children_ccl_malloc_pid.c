#include "../minishell.h"

// señorita your cat cat ls :)
// life is a waste of time, so get wasted all the time
void	child_ccl(t_data *data, t_child *kid)
{
	char	*line;

	if (ft_strcmp(kid->commands[0], "cat"))
		return ;
	if(data->no_cats == 1)
	{
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	if (data->ccl_token == 0)
		return ;
	line = NULL;
	sig_controler(4);
	while (data->ccl_token > 0)
	{
		line = readline("");
		if (!line)
			break ;
		free(line);
		data->ccl_token--;
	}
	free_kid(kid);
	exit_function(data, NULL, 1);
	return ;
}

int	is_string_in_matrix(char **matrix, char *wanted)
{
	int i;

	i = 0;
	while(matrix[i])
	{
		if(!ft_strcmp(matrix[i], wanted))
			return (1);
		i++;
	}
	return (0);
}

void	is_ccl(t_data *data)
{
	int	i;

	i = 0;
	data->no_cats = 0;
	data->ccl_token = 0;
	if (data->pipe_count == 0)
		return ;
	if(is_string_in_matrix(data->args, "<<"))
	{
		data->no_cats = 1;
		return ;
	}
	while (!ft_strcmp(data->args[i], "cat"))
	{
		i++;
		data->ccl_token++;
		if (!ft_strcmp(data->args[i], "|"))
			i++;
		if (!ft_strcmp(data->args[i], "ls"))	
			return ;
	}
	data->ccl_token = 0;
	return ;
}

void	malloc_pid(t_data *data, t_child *kid)
{
	int	i;

	i = 0;
	if (!data->args)
		return ;
	while (data->args[i + 1])
		i++;
	if (data->args[i][0] == '|')
		data->pipe_count--;
	kid->pid = malloc(sizeof(int) * (data->pipe_count + 1));
	if (!kid->pid)
		return ;
	//is_ccl(data);
	return ;
}
