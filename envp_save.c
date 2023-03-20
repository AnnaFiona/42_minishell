#include "minishell.h"

void	get_pwd(t_data *data)
{
	char	*buf;

	buf = malloc(sizeof(char) * 1000);
	if (!buf)
		malloc_exit(data, NULL);
	getcwd(buf, 1000);
	data->saved_pwd = ft_strdup(buf);
	free (buf);
	return ;
}

int	size_2d(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**save_envp(char **envp)
{
	char	**matrix;
	int		len;
	int		i;

	i = 0;
	len = size_2d(envp) + 1;
	matrix = (char **) malloc(len * sizeof(char *));
	if (!matrix)
		malloc_exit(NULL, NULL);
	while (envp[i])
	{
		matrix[i] = ft_strdup(envp[i]);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
