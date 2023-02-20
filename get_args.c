#include "minishell.h"

static void	set_data_quote(t_data *data, char *arg, char quote, int x)
{
	if (data->quote != '\0' && find_second_quote(arg, quote, x) == -1)
		return ;
	if (data->quote == '\0')
		data->quote = quote;
	else if (data->quote == '\'')
		data->quote = '\0';
	else if (data->quote == '"')
		data->quote = '\0';
	return ;
}

static void	cut_quotes(t_data *data, int y, int x)
{
	char	*front;
	char	*back;

	set_data_quote(data, data->args[y], data->args[y][x], x);
	front = ft_substr(data->args[y], 0, x);
	back = ft_substr(data->args[y], x + 1, ft_strlen(data->args[y] + x));
	free(data->args[y]);
	data->args[y] = ft_strjoin(front, back);
	ft_printf("front: %s\n", front);
	ft_printf("back: %s\n", back);
	free(front);
	free(back);
	return ;
}

static char	*variable_name(char *arg, int x)
{
	char	*var_name;
	int		len;

	len = 0;
	while (arg[x + len] && arg[x + len] != ' ' && \
			arg[x + len] != '"' && arg[x + len] != '\'')
		len++;
	var_name = ft_substr(arg, x + 1, len);
	return (var_name);
}

static void	replace_variables(t_data *data, int y, int x)
{
	char	*front_and_var;
	char	*variable;
	char	*var_name;
	char	*front;
	char	*back;

	var_name = variable_name(data->args[y], x);
	variable = ft_getenv(var_name);
	front = ft_substr(data->args[y], 0, x);
	back = ft_substr(data->args[y], x + ft_strlen(var_name) + 1, \
			ft_strlen(data->args[y] + x));
	
	free (data->args[y]);
	front_and_var = ft_strjoin(front, variable);
	data->args[y] = ft_strjoin(front_and_var, back);
	free(front_and_var);
	free(variable);
	free(var_name);
	free(front);
	free(back);
	return ;
}

void	finish_input(t_data *data, char **args)
{
	int	y;
	int	x;

	y = 0;
	data->quote = '\0';
	while(args[y])
	{
		x = 0;
		while (args[y][x])
		{
			if (args[y][x] == '\'' || args[y][x] == '"')
			{
				if (data->quote == '\0' || data->quote == args[y][x])
					cut_quotes(data, y, x);
			}
			if (args[y][x] == '$' && data->quote == '\'')
				replace_variables(data, y, x);
			x++;
		}
		y++;
	}
}

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
	finish_input(data, data->args);
	return ;
}
