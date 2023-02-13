
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_data
{
	char	**args;
	char	**path;
	char	**env;
	char	*prompt;
	char	*line;
}	t_data;

//change_dir.c
void	change_dir(t_data *data);

//envp_to_path.c
void	envp_to_path(t_data *data, char **envp);

//frees.c
void	free_double_array(char **arrarr);
void	free_data(t_data *data);
void    exit_function(t_data *data, char *error_message, int error);

//signals.c
void	ctrl_d_exit(t_data *data);
void	sig_controler(int status);

//split_input.c
void	split_line(t_data *data, char *input);

//terminal.c
void	terminal_loop(t_data *data);
void	get_prompt(t_data *data);

#endif