#include "minishell.h"

static int	replace_with_dash(t_data *data, int y)
{
	char	*arg_without_wave;

	if(ft_strcmp(data->args[y], "~") == 0)
	{
		free(data->args[y]);
		data->args[y] = ft_strdup(getenv("HOME"));
		return (1);
	}
	arg_without_wave = ft_substr(data->args[y], 1, ft_strlen(data->args[y]) - 1);
	free(data->args[y]);
	data->args[y] = strdup_or_strjoin("/", arg_without_wave);
	free(arg_without_wave);
	return (1);
}

static int	replace_home_path(t_data *data, int y)
{
	char	*home_path;
	char	*arg_without_wave;
	int		len;

	home_path = ft_strdup(getenv("HOME"));
	if (home_path == NULL)
		return (1);
	arg_without_wave = ft_substr(data->args[y], 1, ft_strlen(data->args[y]) - 1);
	free(data->args[y]);
	data->args[y] = strdup_or_strjoin(home_path, arg_without_wave);
	len = ft_strlen(home_path);
	free(arg_without_wave);
	free(home_path);
	return (len);
}

int	replace_path(t_data *data, int y)
{
	int len;

	len = 0;
	if(!data->args[y])
		return(0);
	if (data->args[y][0] == '~' && data->args[y][1] != '"' \
		&& data->args[y][1] != '\'')
	{
		if (data->args[y][1] == '/')
			len = replace_home_path(data, y);
		else
			len = replace_with_dash(data, y);
	}
	return (len);
}
