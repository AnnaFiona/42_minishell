#include "../minishell.h"

char	*ft_strmerge_free_s2(char *s1, char *s2)
{
	int		x;
	int		y;
	char	*str;

	if (!s2)
	{
		(s2 = malloc(1));
		s2[0] = '\0';
	}
	x = 0;
	y = 0;
	str = malloc((ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[x])
	{
		str[x] = s1[x];
		x++;
	}
	while (s2[y])
		str[x++] = s2[y++];
	free(s2);
	str[x] = '\0';
	return (str);
}

char	*remove_dot_slash(char **matrix)
{
	int		i;
	char	*tmp;
	char	*path;
	int		not_first;

	i = 0;
	tmp = NULL;
	path = NULL;
	not_first = 0;
	while (matrix[i])
	{
		if (matrix[i] && ft_strcmp(matrix[i], "."))
		{
			if (not_first == 0)
				tmp = ft_strdup(matrix[i]);
			else
				tmp = ft_strjoin("/", matrix[i]);
			not_first = 1;
			path = ft_strmerge(path, tmp);
			free(tmp);
		}
		i++;
	}
	return (path);
}

char	*ft_join_and_remove_dots(char **matrix, char *path)
{
	char	*tmp;

	tmp = NULL;
	tmp = remove_dot_slash(matrix);
	free(path);
	path = ft_strjoin("/", tmp);
	free(tmp);
	return (path);
}

char	*ft_cd_with_dot(char *argv, char *data_pwd)
{
	char	*path;
	char	**matrix;

	path = NULL;
	matrix = NULL;
	if (argv[0] != '/')
	{
		path = ft_strjoin(data_pwd, "/");
		path = ft_strmerge(path, argv);
	}
	else
		path = ft_strdup(argv);
	matrix = ft_split(path, '/');
	path = ft_join_and_remove_dots(matrix, path);
	free_double_array(matrix);
	matrix = ft_split(path, '/');
	free(path);
	path = remove_dot_dot_slash(matrix);
	if (!path)
		path = ft_strdup("/");
	free_double_array(matrix);
	return (path);
}
