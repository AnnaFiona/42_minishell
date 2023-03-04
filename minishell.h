
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

# define SIG_DEFAULT 0
# define SIG_KID 1
# define SIG_PARRENT 2
# define SIG_HEREDOC 3


extern int global_in_fd_copy;

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
	char		*in_quotes;
	char		*prompt;
	char		*line;
	char		quote;
	int			exit_status;
	int			pipe_count;
	int			ccl_token;
	int			len_env;
	int			args_y;
	int			protec;
	int			no_cats;
}				t_data;

typedef struct s_child
{
	char	**commands;
	char	**doc_matrix;
	int		*doc_len;
	char	*in_quotes;
	int		*pipe_fd;
	int		outfile_fd;
	int		guard_fork;
	int		infile_fd;
	int		input_fd;
	int		count;
	int		*pid;
}			t_child;

typedef struct s_here
{
	int 	len;
	int 	range;
	int		index;
	int		token;
	int		arrows;
	char	*line;
	char	**order;
	struct 	s_data *data;
}			t_here;

typedef struct s_index_doc
{
	char	*doc_line;
	int		cut_len;
}			t_index_doc;


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

//children_arrows_utils.c
void	is_it_a_token(t_data *data, t_child *kid, char **commands, int y);
void	cut_token(t_child *kid, int to_cut);

//children_arrows.c
void	search_for_arrows(t_data *data, t_child *kid);

//children_ccl_malloc_pid.c
void 	child_ccl(t_data *data, t_child *kid);
void 	malloc_pid(t_data *data, t_child *kid);

//children_path.c
char	*get_path(t_data *data, t_child *kid, char **paths, char *command);

//children_utils.c
void	count_pipes(t_data *data);
void	get_commands(t_data *data, t_child *kid, char **args);
void	wait_for_children(t_data *data, t_child *kid);

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

//get_args_quotes.c
int		cut_quotes(t_data *data, int y, int x);
char	*strdup_or_strjoin(char const *s_1, char const *s_2);
int		replace_variables(t_data *data, int y, int x);

//get_args_utils.c
int		find_second_quote(char *line, char quote, int x);
int		search_for_break(t_data *data, char *line, char *breakers, int x);

//get_args.c
void	get_args(t_data *data, char *line);

//heredoc_is_valid.c
void 	free_doc(t_child *kid, t_here *doc);
int		is_valid_heredoc(t_data *data, t_child *kid, t_here *doc);

//heredoc_utils.c
char 	*make_heredoc_line(t_child *kid, t_here *doc);
void 	make_order(t_child *kid, t_here *doc);

//heredoc.c
char	*join_free(char *s1, char *s2);
void	set_pipe_cmd(t_child *kid, t_index_doc *my_doc);
void	free_kid_command(t_child *kid, t_index_doc *my_doc);
//void	search_for_heredoc(t_data *data, t_child *kid);
void	get_heredoc_line(t_data *data, t_child *kid, t_index_doc *my_doc);


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