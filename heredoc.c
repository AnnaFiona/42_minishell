
#include "minishell.h"

static char	*join_free(char *s1, char *s2)
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

static int	is_valid_heredoc(t_child *kid)
{
	int	len;

	if (!kid->commands)
		return (-1);
	len = 0;
	if (!ft_strcmp(kid->commands[0], "<<"))
		return (-1);
	while (ft_strcmp(kid->commands[len], "<<") && kid->commands[len])
		len++;
	if (!kid->commands[len])
		return (-1);
	return (len);
}

static void	free_kid_command(t_child *kid)
{
	int		len;
	int		i;
	int		x;
	char	**tmp;

	i = 0;
	x = 0;
	len = size_2d(kid->commands);
	tmp = (char **)malloc((len - 1) * sizeof(char *));
	if (!kid->commands)
		return ;
	while (i < (len - 2))
	{
		if (!ft_strcmp(kid->commands[x], "<<"))
			x += 2;
		tmp[i] = ft_strdup(kid->commands[x]);
		x++;
		i++;
	}
	tmp[i] = NULL;
	free_double_array(kid->commands);
	kid->commands = tmp;
	return ;
}

char	*make_heredoc_line(t_child *kid, char *buf, int len, int i)
{
	char	*line;
	char	*line_nl;

	line = NULL;
	line_nl = NULL;
	while (ft_strcmp(line, kid->commands[len + 1]))
	{
		i++;
		if (line)
			free(line);
		line = readline("> ");
		if (!line)
		{
			ft_printf("bash: warning: here-document at line");
			ft_printf(" %i delimited by end-of-file ", i);
			ft_printf("wanted `%s')\n", kid->commands[len + 1]);
			break ;
		}
		line_nl = ft_strjoin(line, "\n");
		buf = join_free(buf, line_nl);
	}
	if (line)
		free(line);
	return (buf);
}

int	heredoc(t_child *kid)
{
	int		i;
	int		len;
	int		pipes[2];
	char	*buf;

	len = is_valid_heredoc(kid);
	if (len == -1)
		return (1);
	i = 0;
	buf = NULL;
	buf = make_heredoc_line(kid, buf, len, i);
	free_kid_command(kid);
	if (kid->input_fd != -1)
		close(kid->input_fd);
	pipe(pipes);
	kid->input_fd = dup(pipes[0]);
	write(pipes[1], buf, ft_strlen(buf));
	close(pipes[1]);
	free(buf);
	return (1);
}
