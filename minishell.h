
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
	char	*prompt;
	char	*line;
}	t_data;


//frees.c
void    exit_function(t_data *data, char *error_message, int error);

//terminal.c
void	terminal_loop(t_data *data);
void	get_prompt(t_data *data);

#endif