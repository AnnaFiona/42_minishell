
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

void	kill_child(int sig)
{
	(void)sig;
	exit (0);
	return ;
}

void	new_line(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	return ;
}

void	sig_controler(int status)
{
	if (status == 0)
	{
		signal(SIGINT, str_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 1) // for child prozess, that the signals a default
	{
		signal(SIGINT, kill_child);
		signal(SIGQUIT, SIG_DFL);
	}
	if (status == 2)
	{
		signal(SIGINT, new_line);
		signal(SIGQUIT, SIG_IGN);
	}
	return ;
}