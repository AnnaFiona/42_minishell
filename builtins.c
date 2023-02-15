
#include "minishell.h"

int	dubble_strchar(char **ary, char c)
{
	int	i;

	i = 0;
	while (ary[i])
	{
		if (ft_strchr(ary[i], c))
			return (1);
		i++;
	}
	return (0);
}

void	ft_cd(t_data *data)
{
	if (ft_strlen(data->args[0]) > 2)
		ft_printf("cd..: command not found\n");
	else if (data->args[1] == NULL)
		chdir(getenv("HOME"));
	else if (chdir(data->args[1]))
		perror("Error ");
	return ;
}

int	builtins(t_data *data)
{
	if (data->args == NULL)
		return (0);
	count_pipes(data);
	if (dubble_strchar(data->args, '|') || data->pipe_count > 0)
		return (1);
	else if (ft_strncmp(data->args[0], "exit", 4) == 0)
		exit_function(data, NULL, 0);
	else if (ft_strncmp(data->args[0], "cd", 2) == 0)
		ft_cd(data);
	else
		return (1);
	return (0);
}