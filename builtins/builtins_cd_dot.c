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
	int		not_first;
	char	*path;
	char	*tmp;

	i = 0;
	tmp = NULL;
	not_first = 0;
	path = NULL;
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
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
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

int	how_many_returns(char **matrix, int i)
{
	int	back_count;

	back_count = 0;
	while (i >= 0)
	{
		if (!ft_strcmp(matrix[i], ".."))
			back_count += 2;
		else if (ft_strcmp(matrix[i], "."))
			return (back_count);
		i--;
	}
	return (back_count);
}

char	*remove_dot_dot_slash(char **matrix)
{
	int		len_matrix;
	char	*path;
	char	*tmp;

	tmp = NULL;
	path = NULL;
	len_matrix = size_2d(matrix) - 1;
	while (len_matrix >= 0)
	{
		len_matrix -= how_many_returns(matrix, len_matrix);
		if (len_matrix < 0)
		{
			if (path && path[0] != '/')
				path = ft_strmerge_free_s2("/", path);
			return (path);
		}
		if (matrix[len_matrix] && ft_strcmp(matrix[len_matrix], ".."))
		{
			tmp = ft_strjoin("/", matrix[len_matrix]);
			path = ft_strmerge_free_s2(tmp, path);
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
		}
		len_matrix--;
	}
	return (path);
}

char	*ft_cd_with_dot(char *argv, char *data_pwd)
{
	char *path;
	char **matrix;

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