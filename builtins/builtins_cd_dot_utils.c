#include "../minishell.h"

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

char	*join_matrix_expect_dot_dot(char *matrix_line, char *path)
{
	char	*tmp;

	tmp = NULL;
	if (matrix_line && ft_strcmp(matrix_line, ".."))
	{
		tmp = ft_strjoin("/", matrix_line);
		path = ft_strmerge_free_s2(tmp, path);
		free(tmp);
	}
	return (path);
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
		path = join_matrix_expect_dot_dot(matrix[len_matrix], path);
		len_matrix--;
	}
	return (path);
}
