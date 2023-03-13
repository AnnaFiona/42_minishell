#include "../minishell.h"

void	free_line(t_data *data, t_index_doc *my_doc)
{
	int	i;

	i = 0;
	while (i <= data->pipe_count)
	{
		if (my_doc[i].doc_line)
			free(my_doc[i].doc_line);
		i++;
	}
	return ;
}

static void	no_execve(t_data *data, t_child *kid)
{
	char	*path;

	path = ft_getenv(data, "PATH");
	if (kid->commands[0][0] == '/' || !path)
	{
		write(2, "minishell: ", 11);
		write(2, kid->commands[0], ft_strlen(kid->commands[0]));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, kid->commands[0], ft_strlen(kid->commands[0]));
		write(2, ": command not found\n", 20);
	}
	if (!path)
		free(path);
	free_kid(kid);
	exit_function(data, NULL, 3);
}

static void	export_or_env(t_data *data, t_child *kid)
{
	if (!ft_strcmp(kid->commands[0], "export"))
	{
		sort_env(data, data->env);
		free_kid(kid);
		exit_function(data, NULL, 0);
	}
	if (!ft_strcmp(kid->commands[0], "env"))
	{
		ft_print_env(data);
		free_kid(kid);
		exit_function(data, NULL, 0);
	}
	return ;
}

void	child_process(t_data *data, t_child *kid)
{
	char	*path;

	path = NULL;
	change_pwd_mode(data, kid);
	sig_controler(SIG_KID);
	dup_input_output(data, kid);
	if (kid->commands == NULL || kid->commands[0] == NULL)
	{
		free_kid(kid);
		exit_function(data, NULL, 0);
	}
	export_or_env(data, kid);
	path = get_path(data, kid, kid->commands[0]);
	if (path == NULL)
		no_execve(data, kid);
	execve(path, kid->commands, data->env);
}
