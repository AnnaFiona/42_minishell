
#include "minishell.h"

void	str_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

//maybe we need more signals delete if not
//chils should not use this signals
void	sig_controler(int status)
{
	if (status == 0)
	{
		signal(SIGINT, str_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 1) // for child prozess, that the signals a default
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return ;
}