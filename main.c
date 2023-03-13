
#include "minishell.h"

int			g_in_fd_copy;

static void	initialize_data(t_data *data)
{
	data->env_list = NULL;
	data->tokens = ft_split("< > >> <<", ' ');
	data->tokens_pipe = ft_split("< > >> << |", ' ');
	data->args = NULL;
	data->path = NULL;
	data->env = NULL;
	data->in_quotes = NULL;
	data->prompt = NULL;
	data->line = NULL;
	data->saved_pwd = NULL;
	data->quote = '\0';
	data->exit_status = 0;
	data->pipe_count = -1;
	data->guard_fork = 0;
	data->args_y = -1;
	data->len_env = 0;
	data->protec = 0;
	g_in_fd_copy = 0;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	sig_controler(SIG_DEFAULT);
	data = malloc(sizeof(t_data));
	if (!data)
		malloc_exit(NULL, NULL);
	initialize_data(data);
	data->env_ori = envp;
	get_prompt(data);
	data->env = save_envp(envp);
	data->len_env = size_2d(data->env);
	matrix_to_list(data, data->env, &data->env_list);
	terminal_loop(data);
	exit_function(data, NULL, 0);
	return (0);
}

void	print_double_array(char **arrarr)
{
	int	y;

	y = 0;
	if (arrarr == NULL)
		return ;
	while (arrarr[y])
	{
		ft_printf("%s\n", arrarr[y]);
		y++;
	}
}

char	*ft_getenv(t_data *data, char *var)
{
	t_env_list	*tmp;

	if (!var)
		return (NULL);
	tmp = data->env_list;
	while (tmp != NULL)
	{
		if (!ft_strcmp(var, tmp->var))
		{
			if(!tmp->value)
				return (NULL);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (NULL);
}
