#include "minishell.h"

static void	put_list_in_double_array(t_data *data, t_list **head)
{
	t_list	*temp;
	int		y;

	y = 0;
	temp = (*head);
	data->args = malloc(sizeof(char *) * (ft_lstsize(*head) + 1));
	while (temp != NULL)
	{
		data->args[y] = temp->content;
		temp = temp->next;
		y++;
	}
	data->args[y] = NULL;
	while ((*head) != NULL)
	{
		temp = (*head);
		(*head) = (*head)->next;
		free(temp);
	}
	return ;
}

static void	split_line(t_data *data, t_list **head, char *line)
{
	int	len;
	int	x;

	x = 0;
	while (line[x])
	{
		len = 0;
		while (line[x] == ' ')
			x++;
		if (line[x] == '\0')
			break ;
		len = search_for_break(data, line, "\"\'<>| ", x);
		ft_lstadd_back(head, ft_lstnew(ft_substr(line, x, len)));
		x += len;
	}
}

void	get_args(t_data *data, char *line)
{
	t_list	*head;

	if (line[0] == '\0')
		return ;
	head = NULL;
	split_line(data, &head, line);
	put_list_in_double_array(data, &head);
	free(line);
	data->line = NULL;
	return ;
}
