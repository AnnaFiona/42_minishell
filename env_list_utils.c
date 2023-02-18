
#include "minishell.h"

void	print_env_list(t_env_list *top)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		ft_printf("var:   %s\n", top->var);
		if(top->value != NULL)
			ft_printf("value: %s\n", top->value);
		top = top->next;
		i++;
	}
	ft_printf("list with %i entries", i);
	return ;
}

void	free_env_list(t_env_list **top)
{
	t_env_list	*temp;

	if (*top == NULL)
		return ;
	while (*top != NULL)
	{
		temp = *top;
		*top = (*top)->next;
		free(temp->var);
		if(temp->value != NULL)
			free(temp->value);
		free(temp);
	}
}

int	size_of_list(t_env_list *top)
{
	int i;

	i = 0;
	while (top != NULL)
	{
		top = top->next;
		i++;
	}
	return (i);
}