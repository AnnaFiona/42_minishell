
#include "minishell.h"

void	ft_cd(t_data *data)
{
	if (data->args[1] == NULL)
		chdir(getenv("HOME"));
	else if (chdir(data->args[1]))
		perror("Error ");
	return ;
}

int	builtins(t_data *data)
{
	count_pipes(data);
	if (data->pipe_count > 0)
		return (1);
	else if (!ft_strcmp(data->args[0], "exit"))
		exit_function(data, "exit", 0);
	else if (!ft_strcmp(data->args[0], "cd"))
		ft_cd(data);
	else if (!ft_strcmp(data->args[0], "export"))
		ft_export(data);
	else
		return (1);
	return (0);
}
