#include "../minishell.h"

void	malloc_pid(t_data *data, t_child *kid)
{
	kid->pid = malloc(sizeof(int) * (data->pipe_count + 1));
	if (!kid->pid)
		malloc_exit(data, kid);
	return ;
}

static void	dup_input(t_child *kid)
{
	if (kid->pipe_fd[0] != -1)
		close(kid->pipe_fd[0]);
	if (kid->pipe_fd[1] != -1)
	{
		kid->output_fd = dup(kid->pipe_fd[1]);
		close(kid->pipe_fd[1]);
	}
	return ;
}

static void	dup_input_output(t_data *data, t_child *kid)
{
	int	out;
	int	in;

	dup_input(kid);
	search_for_arrows(data, kid);
	if (kid->input_fd != -1)
	{
		in = dup2(kid->input_fd, STDIN_FILENO);
		close(kid->input_fd);
		kid->input_fd = dup(in);
	}
	if (kid->output_fd != -1)
	{
		out = dup2(kid->output_fd, STDOUT_FILENO);
		close(kid->output_fd);
		kid->output_fd = dup(out);
	}
	if (!kid->commands[0])
	{
		free_kid(kid);
		exit_function(data, NULL, 0);
	}
	return ;
}

void change_pwd_mode(t_data *data, t_child *kid)
{
	char **tmp;

	if(!ft_strcmp(kid->commands[0], "cd"))
	{
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	if(!ft_strcmp(kid->commands[0], "pwd") && !kid->commands[1])
	{
		tmp = malloc(sizeof(char *) * 3);
		if (!tmp)
			malloc_exit(data, kid);
		tmp[0] = ft_strdup(kid->commands[0]);
		tmp[1] = ft_strdup("-L");
		tmp[2] = NULL;
		free_double_array(kid->commands);
		kid->commands = tmp;
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
	if (!ft_strcmp(kid->commands[0], "export"))
	{
		if (kid->commands[1] == NULL)
			sort_env(data, data->env);
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	path = get_path(data, kid, data->path, kid->commands[0]);
	if (path == NULL)
	{
		if (kid->commands[0][0] == '/')
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
		free_kid(kid);
		exit_function(data, NULL, 1);
	}
	execve(path, kid->commands, data->env);
}
