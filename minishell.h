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
# include <dirent.h>
# include <sys/types.h>

# define SIG_DEFAULT 0
# define SIG_KID 1
# define SIG_PARRENT 2
# define SIG_HEREDOC 3
# define NO_CHILDS 0
# define MAKE_CHILDS 1

extern int	g_in_fd_copy;

typedef struct s_env_list
{
	char				*var;
	char				*value;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_data
{
	t_env_list	*env_list;
	char		**tokens_pipe;
	char		**tokens;
	char		**args;
	char		**path;
	char		**env;
	char		**env_ori;
	char		*in_quotes;
	char		*prompt;
	char		*line;
	char		*saved_pwd;
	char		quote;
	int			exit_status;
	int			pipe_count;
	int			guard_fork;
	int			len_env;
	int			args_y;
	int			protec;
}				t_data;

typedef struct s_child
{
	char	**commands;
	char	**doc_matrix;
	int		*doc_len;
	char	*in_quotes;
	int		*pipe_fd;
	int		*pid;
	int		output_fd;
	int		input_fd;
	int		count;
}			t_child;

typedef struct s_here
{
	int				len;
	int				range;
	int				index;
	int				token;
	int				arrows;
	char			*line;
	char			**order;
	struct s_data	*data;
}			t_here;

typedef struct s_index_doc
{
	char	*doc_line;
	int		cut_len;
}			t_index_doc;

//builtins_cd_remove_end.c
char	*remove_end(char *str, char c);
int		remove_last_char(t_data *data, char *pwd, char *path);

//builtins_cd_save_pwd.c
void	secure_pwd(t_data *data, char *path);
void	save_pwd(t_data *data, char *pwd, char *path);

//builtins_cd_utils.c
int		chdir_error_msg(t_data *data, char *path);
int		is_last_char(char *str, char c);
char	*rm_last_char(char *str);
char	*save_relative_path(char *old_path, char *path);

//builtins_cd.c
int		ft_cd(t_data *data, t_child *kid, char *path);

//builtins_env_list_to_matrix.c
void	save_path_in_data(t_data *data, char *value);
void	env_list_to_matrix(t_data *data, char equalsign);

//builtins_export_sort.c
void	sort_env(t_data *data, char **env);

//builtins_export_utils.c
int		ft_strcmp(const char *s1, const char *s2);
int		is_dublicate(t_data *data, char *var, char *value);
int		is_dub_in_ori(t_data *data, char *var, char *value);

//builtins_export.c
void	ft_export(t_data *data, t_child *kid);

//builtins_ori_env_test.c
char	*export_pwd_null(t_data *data, char *var);
int		is_in_ori_env(t_data *data, char *var);

//builtins_unset.c
void	ft_unset(t_data *data, t_child *kid);

//builtins.c
void	ft_print_env(t_data *data);
int		builtins(t_data *data);
int		builtins_in_kid(t_data *data, t_child *kid);

//children_arrows_utils.c
void	cut_token(t_child *kid, int to_cut);

//children_arrows.c
void	search_for_arrows(t_data *data, t_child *kid);

//children_process_utils.c
void	close_pipes_and_free(t_data *data, t_child *kid);
void	malloc_pid(t_data *data, t_child *kid);
void	dup_input_output(t_data *data, t_child *kid);
void	change_pwd_mode(t_data *data, t_child *kid);

//children_process.c
void	free_line(t_data *data, t_index_doc *my_doc);
void	child_process(t_data *data, t_child *kid);

//children_path_utils.c
char	*is_absolute_path(t_data *data, t_child *kid, char *cmd);

//children_path.c
char	*get_path(t_data *data, t_child *kid, char *command);

//children_utils.c
int		count_pipes(t_data *data);
void	get_commands(t_data *data, t_child *kid, char **args);
void	wait_for_children(t_data *data, t_child *kid);
void	set_exit_status(t_data *data);

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

//envp_save.c
int		size_2d(char **envp);
char	**save_envp(char **envp);

//exit.c
void	exit_function(t_data *data, char *error_message, int error);
void	end_minishell(t_data *data, t_child *kid);
void	malloc_exit(t_data *data, t_child *kid);
void	ctrl_d_exit(t_data *data);

//frees.c
void	free_double_array(char **arrarr);
void	free_kid(t_child *kid);
void	free_data(t_data *data);

//get_args_cut_args.c
void	cut_arg(t_data *data, int to_cut);

//get_args_path.c
int		replace_path(t_data *data, int y);

//get_args_quotes.c
int		cut_quotes(t_data *data, int y, int x);
char	*strdup_or_strjoin(char const *s_1, char const *s_2);

//get_args_syntax_errors.c
int		check_pipes(t_data *data);
void	search_syntax_errors(t_data *data);

//get_args_utils.c
int		find_second_quote(char *line, char quote, int x);
int		search_for_break(t_data *data, char *line, char *breakers, int x);

//get_args_variables.c
int		replace_variables(t_data *data, int y, int x);

//get_args.c
void	get_args(t_data *data, char *line);

//heredoc_free_kid_cmd.c
int		count_fill_order(t_child *kid, t_here *doc, char fill);
void	set_pipe_cmd(t_child *kid, t_index_doc *my_doc);
void	free_kid_command(t_child *kid, t_index_doc *my_doc);

//heredoc_is_valid.c
int		is_valid_heredoc(t_data *data, t_child *kid, t_here *doc);
void	make_order(t_child *kid, t_here *doc);

//heredoc_utils.c
char	*make_heredoc_line(t_data *data, t_child *kid, t_here *doc);

//heredoc.c
void	get_heredoc_line(t_data *data, t_child *kid, t_index_doc *my_doc);

//signals.c
void	sig_controler(int status);

//terminal.c
void	terminal_loop(t_data *data);
void	get_prompt(t_data *data);

//main.c
void	print_double_array(char **arrarr);
char	*ft_getenv(t_data *data, char *var);

#endif