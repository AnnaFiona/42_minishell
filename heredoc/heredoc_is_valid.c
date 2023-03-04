
#include "../minishell.h"

void	free_doc(t_child *kid, t_here *doc)
{
	free_kid(kid);
	if (doc->line)
		free(doc->line);
	if (doc->order)
		free_double_array(doc->order);
	free(doc);
}

static void	heredoc_syntax_error(t_data *data, t_child *kid, char *token)
{
	if (token == NULL)
	{
		if (data->pipe_count == 0 || data->pipe_count == kid->count)
		{
			ft_printf("minishell: syntax error ");
			ft_printf("near unexpected token 'newline'\n");
		}
		else
			ft_printf("minishell: syntax error near unexpected token '|'\n");
	}
	else
	{
		ft_printf("minishell: syntax error near ");
		ft_printf("unexpected token '%s'\n", token);
	}
	return ;
}

static char	*heredoc_is_token(char *cmd)
{
	int		y;
	char	*error_token;
	char	**token_str;
	
	y = 0;
	token_str = ft_split("|| && & ; ;; ;& ;;& | |& ( ) ' <<< << < >> >", ' ');
	while(token_str[y])
	{
		if(!ft_strncmp(cmd, token_str[y], ft_strlen(token_str[y])))
		{
			error_token = ft_strdup(token_str[y]);
			free_double_array(token_str);
			return (error_token);
		}
		y++;
	}
	free_double_array(token_str);
	return (NULL);
}

static int	herdoc_token(t_data *data, t_child *kid, char **cmd, int i)
{
	char *error_token;

	error_token = NULL;
	if (cmd[i] == NULL)
	{
		kid->guard_fork = 1;
		heredoc_syntax_error(data, kid, cmd[i]);
		return (-1);
	}
	error_token = heredoc_is_token(cmd[i]);
	if (error_token && kid->in_quotes[i] != 'q')
	{
		kid->guard_fork = 1;
		heredoc_syntax_error(data, kid, error_token);
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
