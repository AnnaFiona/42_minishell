#include "../minishell.h"

int	chdir_error_msg(t_data *data, char *path)
{
	if (chdir(path))
	{
		data->exit_status = 1;
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		return (-1);
	}
	return (0);
}

int	is_last_char(char *str, char c)
{
	int	len;

	if (!str || str[0] == '\0')
		return (1);
	if (!ft_strcmp(str, "..") || !ft_strcmp(str, "/"))
	{
		return (1);
	}
	len = ft_strlen(str);
	if (str[len - 1] == c)
		return (0);
	return (1);
}

char	*rm_last_char(char *str)
{
	int		i;
	int		len;
	char	*new;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = malloc(sizeof(char) * len);
	if (!new)
		malloc_exit(NULL, NULL);
	i = 0;
	len--;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*save_relative_path(char *old_path, char *path)
{
	char	*tmp;
	char	*new_path;

	tmp = NULL;
	new_path = NULL;
	if (!ft_strcmp(old_path, "/"))
	{
		new_path = ft_strjoin(old_path, path);
		free(path);
		return (new_path);
	}
	else
	{
		tmp = ft_strjoin(old_path, "/");
		new_path = ft_strjoin(tmp, path);
	}
	free(tmp);
	free(path);
	return (new_path);
}
