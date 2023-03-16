#include "../minishell.h"

char	*export_pwd_null(t_data *data, char *var)
{
	char	*value;

	value = NULL;
	if (ft_strcmp(var, "PWD"))
		return (value);
	value = ft_strdup(data->saved_pwd);
	return (value);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	is_dublicate(t_data *data, char *var, char *value)
{
	t_env_list	*tmp;

	tmp = data->env_list;
	while (tmp != NULL)
	{
		if (ft_strcmp(var, tmp->var) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
