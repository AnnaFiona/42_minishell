#include "minishell.h"

static int	find_second_quote(char *line, char quote, int x)
{
	int	len;

	len = 0;
	x++;
	while (line[x + len] && line[x + len] != quote)
		len++;
	if (line[x + len] == '\0')
		return (-1);
	return (len);
}

static int	which_breaker(char *line, char breaker, int x, int y)
{
	int	len;

	len = 0;
	if (breaker == ' ')
		return (0);
	if (breaker == '"' || breaker == '\'')
	{
		len = find_second_quote(line, breaker, x);
		if (len != -1)
		{
			if (y != 0)
				return (0);
			len += 2;
		}
	}
	else if (y == 0 && (breaker == '<' || breaker == '>'))
	{
		len++;
		if (line[x + 1] == breaker)
			len++;
	}
	else if (y == 0 && breaker == '|')
		len = 1;
	return (len);
}

//find_second_quote returns -1 if there is no second quote

static int	search_for_break(char *line, char *breakers, int x)
{
	int	check;
	int	len;
	int	y;

	len = 0;
	while (line[x + len])
	{
		y = 0;
		while (breakers[y])
		{
			check = 0;
			if (line[x + len] == breakers[y])
			{
				check = which_breaker(line, breakers[y], x + len, len);
				if (check != -1)
				{
					len += check;
					return (len);
				}
			}
			y++;
		}
		len++;
	}
	return (len);
}

//////////////////////////////////////////////
void	print_list(t_list *head)
{
	while(head != NULL)
	{
		ft_printf("list: %s\n", head->content);
		head = head->next;
	}
	return ;
}

void	print_double_array(char **arrarr)
{
	int	y;

	y = 0;
	while(arrarr[y] != NULL)
	{
		ft_printf("array: %s\n", arrarr[y]);
		y++;
	}
	return ;
}
//////////////////////////////////////////////

static void	put_list_in_double_array(t_data *data, t_list **head)
{
	t_list *temp;
	int	y;

	y = 0;
	temp = (*head);
	data->args = malloc(sizeof(char *) * (ft_lstsize(*head) + 1));
	while(temp != NULL)
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

void	split_line(t_data *data, char *line)
{
	t_list	*head;
	int		len;
	int		x;

	if (line[0] == '\0')
		return ;
	x = 0;
	head = NULL;
	while (line[x])
	{
		len = 0;
		while (line[x] == ' ')
			x++;
		if (line[x] == '\0')
			break ;
		len = search_for_break(line, "\"\'<>| ", x);
		ft_lstadd_back(&head, ft_lstnew(ft_substr(line, x, len)));
		x += len;
	}
	put_list_in_double_array(data, &head);
	print_double_array(data->args);
	free(line);
	data->line = NULL;
	return ;
}
