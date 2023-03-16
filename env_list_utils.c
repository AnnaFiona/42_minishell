#include "minishell.h"

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
		if (temp->value != NULL)
			free(temp->value);
		free(temp);
	}
}

int	size_of_list(t_env_list *top)
{
	int	i;

	i = 0;
	while (top != NULL)
	{
		top = top->next;
		i++;
	}
	return (i);
}
