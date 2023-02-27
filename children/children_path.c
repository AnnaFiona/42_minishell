#include "../minishell.h"
#include <sys/types.h>
#include <dirent.h>

static void	is_dir(t_data *data, t_child *kid, char *cmd)
{
	DIR		*fd;

	fd = opendir(cmd);
	if (fd)
	{
		closedir(fd);
		ft_printf("minishell: %s: Is a directory\n", cmd);
		free_kid(kid);
		exit_function(data, NULL, 0);
	}
	return ;
}

static char	*join_usr(char *cmd)
{
	char	*tmp_trimmed;
	char	*tmp;

	tmp_trimmed = ft_substr(cmd, 1, ft_strlen(cmd) - 1);
	tmp = ft_strjoin("/usr", tmp_trimmed);
	free(tmp_trimmed);
	if (access(tmp, X_OK) != 0)
		return(NULL);
	return (tmp);
}

static char	*is_absolute_path(t_data *data, t_child *kid, char *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (*cmd == '~')
	{
		tmp = join_usr(cmd);
		if (tmp == NULL)
			return (NULL);
		is_dir(data, kid, tmp);
		return (tmp);
	}
	if (access(cmd, X_OK) != 0)
		return (NULL);
	is_dir(data, kid, cmd);
	return (cmd);
}

char	*get_path(t_data *data, t_child *kid, char **paths, char *command)
{
	char	*path_with_command;
	char	*temp_path;
	char	*cmd_absolute;
	int		y;

	y = 0;
	cmd_absolute = is_absolute_path(data, kid, command);
	if (cmd_absolute)
		return (cmd_absolute);
	while (paths[y])
	{
		temp_path = ft_strjoin(paths[y], "/");
		path_with_command = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(path_with_command, X_OK) == 0)
			return (path_with_command);
		free (path_with_command);
		y++;
	}
	return (NULL);
}
