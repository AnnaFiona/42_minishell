#include "minishell.h"


static int	get_lvl(char	*value)
{
	int	minus;
	int	lvl;
	int	x;

	x = 0;
	minus = 0;
	if (value == NULL)
		return (1);
	//????^
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

void	increase_shlvl(t_env_list *temp)
{
	int	lvl;

	lvl = get_lvl(temp->value);
	free(temp->value);
	temp->value = ft_itoa(lvl);
	return ;
}

void	set_to_one(t_env_list *temp)
{
	
}


void	set_shlvl(t_env_list *temp)
{
	add_list_end(data, )
}

void	increase_shlvl(data)
{
	t_env_list	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->value, "SHLVL") == 0)
			break;
		temp = temp->next;
	}
	if (temp == NULL)
		set_shlvl(data);
	else if (!temp->value)
		set_to_one(data);
	else if (ft_atoi(temp->value))
		increase_shlvl();
}