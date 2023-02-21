
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env_list
{
	char				*var;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_data
{
	t_env_list	*env_list;
	char		**args;
	char		**path;
	char		**env;
	char		*prompt;
	char		*line;
	char		quote;
	int			pipe_count;
	int			args_y;
	int			len_env;
}				t_data;

typedef struct s_child
{
	char	**commands;
	int		*pipe_fd;
	int		count;
	int		input_fd;
	int		pid;
}			t_child;


//builtins_export_sort.c
void	env_list_to_matrix(t_data *data);
void	sort_env(t_data *data, char **env);

//builtins_export_utils.c
int 	ft_strcmp(const char *s1, const char *s2);
int		is_dublicate(t_data *data, char *var, char *value);
int		is_dub_in_ori(t_data *data, char *var, char *value);

//builtins_export.c
void	ft_export(t_data *data);

//builtins.c
int		builtins(t_data *data);

//children_utils.c
void	count_pipes(t_data *data);
char	*get_path(char **paths, char *command);
char	**get_commands(t_data *data, char **args);
void	wait_for_children(t_data *data);

//children.c
void	redirect_children(t_data *data);

//env_list_utils.c
void	print_env_list(t_env_list *top);
void	free_env_list(t_env_list **top);
int		size_of_list(t_env_list *top);

//env_list.c
void	add_list_end(t_data *data, t_env_list *top, char *var,
			char *value);
void	matrix_to_list(t_data *data, char **env,
			t_env_list **list);

//envp_to_path.c
int		size_2d(char **envp);
void	envp_to_path(t_data *data, char **envp);
char	**save_envp(char **envp);

//frees.c
void	free_double_array(char **arrarr);
void	free_kid(t_child *kid);
void	free_data(t_data *data);
void	exit_function(t_data *data, char *error_message, int error);

//get_args_utils.c
int		find_second_quote(char *line, char quote, int x);
int		search_for_break(t_data *data, char *line, char *breakers, int x);

//get_args.c
void	get_args(t_data *data, char *line);

//signals.c
void	ctrl_d_exit(t_data *data);
void	sig_controler(int status);

//terminal.c
void	terminal_loop(t_data *data);
void	get_prompt(t_data *data);

//main.c
void	print_double_array(char **arrarr);
char	*ft_getenv(t_data *data, char *var);

#endif