
#include "minishell.h"

char	*join_free(char *s1, char *s2)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		str = ft_strdup(s2);
		free(s2);
		return (str);
	}
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

void	free_kid_command(t_child *kid)
{
	char *tmp;

	if(!kid->commands)
		return ;
	tmp = ft_strdup(kid->commands[0]);
	free_double_array(kid->commands);
	kid->commands = (char **)malloc(2 * sizeof(char *));
	kid->commands[0] = tmp;
	kid->commands[1] = NULL;
	return ;
}

int		heredoc(t_child *kid)
{
	int pipes[2];
	int i;
	char *line_nl;
	char *line;
	char *line_end;

	kid->heredoc_line = NULL;
	if (ft_strcmp(kid->commands[1], "<<") || !kid->commands[2])
		return (0);
	i = 0;
	line = NULL;
	line_nl = NULL;
	line_end = NULL;
	while (ft_strcmp(line, kid->commands[2]))
	{
		if (line)
			free(line);
		line = readline("> ");
		line_nl = ft_strjoin(line, "\n");
		line_end = join_free(line_end, line_nl);
	}
	free_kid_command(kid);
	if (line)
		free(line);
	if(kid->input_fd != -1)
		close(kid->input_fd);
	pipe(pipes);
	kid->input_fd = dup(pipes[0]);
	write(pipes[1], line_end, ft_strlen(line_end));
	close(pipes[1]);
	return (1);
}