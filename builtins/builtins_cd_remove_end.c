
#include "../minishell.h"

static int	remove_end_malloc(char *str, char c)
{
	int	count;
	int	len;

	len = 0;
	count = 0;
	while (str[len])
	{
		if (str[len] == '/')
			count++;
		if (count > 1)
			break ;
		len++;
	}
	if (count < 2)
		return (-1);
	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == c)
			break ;
		len--;
	}
	return (len);
}

char	*cd_in_first_dir(char *str)
{
	free(str);
	str = malloc(sizeof(char) * 2);
	if (!str)
		exit(12);
	str[0] = '/';
	str[1] = '\0';
	return (str);
}

char	*remove_end(char *str, char c)
{
	int		i;
	int		len;
	char	*tmp;

	if (!str)
		return (NULL);
	if (!ft_strcmp(str, "/"))
		return (str);
	i = 0;
	len = remove_end_malloc(str, c);
	if (len == -1)
		return (cd_in_first_dir(str));
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		malloc_exit(NULL, NULL);
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

int	remove_last_char(t_data *data, char *pwd, char *path)
{
	char	*tmp;

	tmp = NULL;
	if (is_last_char(path, '/') == 0)
	{
		tmp = rm_last_char(path);
		secure_pwd(data, path);
		is_dublicate(data, pwd, tmp);
		if (tmp)
			free(tmp);
		env_list_to_matrix(data, 'x');
		return (1);
	}
	is_dublicate(data, pwd, path);
	return (0);
}
