
#include "../minishell.h"

static int heredoc_is_token(t_data *data, char *cmd)
{
	int		y;

	y = 0;
	while (data->tokens[y])
	{
		if (!ft_strncmp(cmd, data->tokens[y], ft_strlen(data->tokens[y])))
			return (1);
		y++;
	}
	return (0);
}

static int	herdoc_token(t_data *data, t_child *kid, char **cmd, int i)
{
	if (cmd[i] == NULL)
	{
		data->guard_fork = 1;
		return (-1);
	}
	if (heredoc_is_token(data, cmd[i]) && kid->in_quotes[i] != 'q')
	{
		data->guard_fork = 1;
		return (-1);
	}
	return (0);
}

int	is_valid_heredoc(t_data *data, t_child *kid, t_here *doc)
{
	int	i;
	int	len;

	if (!kid->commands)
		return (-1);
	i = 0;
	len = 0;
	while (kid->commands[i])
	{
		if (!ft_strcmp(kid->commands[i], "<<") && herdoc_token(data, kid,
				kid->commands, i + 1) == -1)
		{
			if (len == 0)
				return (-1);
			doc->range = i - 1;
			return (len);
		}
		if (!ft_strcmp(kid->commands[i], "<<"))
			len++;
		i++;
	}
	if (!kid->commands[len])
		return (-1);
	doc->range = size_2d(kid->commands);
	return (len);
}
