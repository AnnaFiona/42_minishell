
#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while(s1[i] || s2[i])
	{
		if(s1[i] != s2[i])
			return(s1[i] - s2[i]);
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
			if(value != NULL)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	is_dub_in_ori(t_data *data, char *var, char *value)
{
	int i;
	t_env_list	*tmp;

	i = 0;
	tmp = data->env_list;
	while(i < data->len_env)
	{
		if (ft_strcmp(var, tmp->var) == 0)
		{
			if(value != NULL)
				return (1);
		}
		i++;
	}
	return (0);
}
