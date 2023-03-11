#include "../minishell.h"

int	find_second_quote(char *line, char quote, int x)
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

static void	switch_data_quote(t_data *data, char *line, char breaker, int x)
{
	int	len;

	len = 0;
	if (data->quote == '\0')
	{
		len = find_second_quote(line, breaker, x);
		if (len == -1)
			return ;
		data->quote = breaker;
	}
	else
		data->quote = '\0';
}

//where_to_break returns -1 if it shouldn't break, or where to break
static int	where_to_break(t_data *data, char breaker, int x, int start)
{
	int	len;

	len = 0;
	if (breaker == '"' || breaker == '\'')
	{
		switch_data_quote(data, data->line, breaker, x);
		return (-1);
	}
	if (data->quote != '\0')
		return (-1);
	if (breaker == ' ')
		return (0);
	else if (start == 0 && (breaker == '<' || breaker == '>'))
	{
		len++;
		if (data->line[x + 1] == breaker)
			len++;
	}
	else if (start == 0 && breaker == '|')
		len = 1;
	return (len);
}

//find_second_quote returns -1 if there is no second quote
int	search_for_break(t_data *data, char *line, char *breakers, int x)
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
				check = where_to_break(data, breakers[y], x + len, len);
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
