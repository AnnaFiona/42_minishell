#include "minishell.h"

static int	get_lvl(char *value)
{
	int	minus;
	int	lvl;
	int	x;

	x = 0;
	minus = 0;
	if (value[0] == '-')
	{
		minus = 1;
		x++;
	}
	while (value[x])
	{
		if (ft_isdigit(value[x]) == 0)
			return (1);
		x++;
	}
	lvl = (int)ft_atoi(value);
	if (lvl < 0)
		return (0);
	return (lvl + 1);
}

static void	increase(t_data *data, t_env_list *temp)
{
	int	lvl;

	lvl = get_lvl(temp->value);
	free(temp->value);
	temp->value = ft_itoa(lvl);
	env_list_to_matrix(data);
	return ;
}

static void	set_to_one(t_data *data)
{
	add_equal_to_list(data, "SHLVL");
	is_dublicate(data, "SHLVL", "1");
	env_list_to_matrix(data);
	return ;
}

static void	set_shlvl(t_data *data)
{
	add_list_end(data, ft_strdup("SHLVL"), ft_strdup("1"), '=');
	env_list_to_matrix(data);
	return ;
}

void	increase_shlvl(t_data *data)
{
	t_env_list	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->var, "SHLVL") == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		set_shlvl(data);
	else if (temp->value == NULL)
		set_to_one(data);
	else
		increase(data, temp);
	return ;
}
