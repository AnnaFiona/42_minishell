#include "../minishell.h"

static void	finish_input(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->quote = '\0';
	while (data->args[y])
	{
		x = replace_path(data, y);
		while (data->args[y] && data->args[y][x])
		{
			if (data->args[y][x] == '\'' || data->args[y][x] == '"')
			{
				if (data->quote == '\0' || data->quote == data->args[y][x])
				{
					if (cut_quotes(data, y, x) == -1)
						x++;
					x--;
				}
				x++;
			}
			else if (data->args[y][x] == '$' && data->quote != '\'')
				x = replace_variables(data, y, x);
			else
				x++;
		}
		if (data->args[y] == NULL)
			break ;
		y++;
	}
}

static void	get_in_quotes(t_data *data)
{
	int	y;

	y = 0;
	while (data->args[y])
		y++;
	data->in_quotes = malloc(sizeof(char) * (y + 1));
	if (!data->in_quotes)
		malloc_exit(data, NULL);
	y = 0;
	while (data->args[y])
	{
		if (data->args[y][0] == '"' || data->args[y][0] == '\'')
			data->in_quotes[y] = 'q';
		else
			data->in_quotes[y] = '-';
		y++;
	}
	data->in_quotes[y] = '\0';
	return ;
}

static void	put_list_in_double_array(t_data *data, t_list **head)
{
	t_list	*temp;
	int		y;

	y = 0;
	temp = (*head);
	data->args = malloc(sizeof(char *) * (ft_lstsize(*head) + 1));
	if (!data->args)
		malloc_exit(data, NULL);
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
	get_in_quotes(data);
	free(line);
	data->line = NULL;
	search_syntax_errors(data);
	if (data->args == NULL)
		return ;
	count_pipes(data);
	finish_input(data);
	if (data->args[0] == NULL)
		data->args = NULL;
	return ;
}
