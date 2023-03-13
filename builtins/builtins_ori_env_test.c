
#include "../minishell.h"

static int	ft_len_to_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == c)
			break ;
	}
	return (i);
}

static int	is_already_there(t_data *data, char *var)
{
	int	i;
	int	len;

	i = 0;
	while (data->env[i])
	{
		len = ft_len_to_char(data->env[i], '=');
		if (!ft_strncmp(var, data->env[i], len))
			return (0);
		i++;
	}
	return (1);
}

int	is_in_ori_env(t_data *data, char *var)
{
	int	i;
	int	ok;
	int	len;

	i = 0;
	ok = -1;
	if (var[i] < 'A' || var[i] > 'Z')
	{
		return (0);
	}
	while (data->env_ori[i])
	{
		len = ft_len_to_char(data->env_ori[i], '=');
		if (!ft_strncmp(var, data->env_ori[i], len))
		{
			if (is_already_there(data, var) == 1)
				data->len_env++;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*export_pwd_null(t_data *data, char *var)
{
	char	*value;

	value = NULL;
	if (ft_strcmp(var, "PWD"))
		return (value);
	value = ft_strdup(data->saved_pwd);
	return (value);
}
