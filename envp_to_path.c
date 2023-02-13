
#include "minishell.h"

int	size_2d(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void 	save_envp(t_data *data, char **envp)
{
	int i;
	int len;

	i = 0;
	len = size_2d(envp) + 1;
	data->env = (char **) malloc(len * sizeof(char *));
	while(envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env[i] = NULL;
	return ;
}

void	envp_to_path(t_data *data, char **envp)
{
	int i;
    char *line;

	i = 0;
    while (envp[i] && ft_strncmp("PATH", envp[i], 4))
		i++;
	line = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	data->path = ft_split(line, ':');
	free(line);
	save_envp(data, envp);
    return ;
}
