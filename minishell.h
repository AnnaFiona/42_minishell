
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
	t_env_list			*env_list;
	char				**args;
	char				**path;
	char				**env;
	char				*prompt;
	char				*line;
	int					pipe_count;
	int					args_y;
}						t_data;

typedef struct s_child
{
	char				**commands;
	int					*pipe_fd;
	int					count;
	int					input_fd;
	int					pid;
}						t_child;

//builtins.c
int						builtins(t_data *data);

//builtins_export.c
void					ft_export(t_data *data);

//builtins_export_sort.c
void					sort_env(t_data *data, char **env);

//builtins_ultils.c
int						ft_strcmp(const char *s1, const char *s2);

//change_dir.c
int						builtins(t_data *data);

//children_utils.c
void					count_pipes(t_data *data);
char					*get_path(char **paths, char *command);
char					**get_commands(t_data *data, char **args);
void					wait_for_children(t_data *data);

//children.c
void					redirect_children(t_data *data);

//env_list_utils.c
void					print_env_list(t_env_list *top);
void					free_env_list(t_env_list **top);

//env_list.c
void					matrix_to_list(t_data *data, char **env,
							t_env_list **list);

//envp_to_path.c
int						size_2d(char **envp);
void					envp_to_path(t_data *data, char **envp);
char					**save_envp(char **envp);

//frees.c
void					free_double_array(char **arrarr);
void					free_data(t_data *data);
void					exit_function(t_data *data, char *error_message,
							int error);

//signals.c
void					ctrl_d_exit(t_data *data);
void					sig_controler(int status);

//split_line.c
void					print_list(t_list *head);
void					split_line(t_data *data, char *input);

//terminal.c
void					terminal_loop(t_data *data);
void					get_prompt(t_data *data);

//main.c
void					print_double_array(char **arrarr);

#endif