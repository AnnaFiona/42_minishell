
#include "minishell.h"

int	size_2d(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**save_envp(char **envp)
{
	int i;
	int len;
	char **matrix;

	i = 0;
	len = size_2d(envp) + 1;
	matrix = (char **) malloc(len * sizeof(char *));
	if (!matrix)
		malloc_exit(NULL, NULL);
	while(envp[i])
	{
		matrix[i] = ft_strdup(envp[i]);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
