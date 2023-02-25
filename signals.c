
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

void	sig_doc(int sig)
{
	(void)sig;
	close(0);
	return ;
}

void	new_line(int sig)
{
	if(sig == SIGINT)
		write(1, "\n", 1);
	if(sig == SIGQUIT)
		write(1, "Error: Core Dumped", 18);
	return ;
}

void	sig_controler(int status)
{
	if (status == 0)
	{
		signal(SIGINT, str_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (status == 2)
	{
		signal(SIGINT, new_line);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 3)
	{
		signal(SIGINT, sig_doc);
		signal(SIGQUIT, SIG_IGN);
	}
	return ;
}