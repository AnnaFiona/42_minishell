
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
	{
		free(str);
		str = malloc(sizeof(char) * 2);
		if (!str)
			exit(12);
		str[0] = '/';
		str[1] = '\0';
		return (str);
	}
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
