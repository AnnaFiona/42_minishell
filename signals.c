
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
	global_heredoc = 1;
	close(0);
	return ;
}

void	new_line(int sig)
{
	if(sig == SIGINT && global_heredoc == 0)
		write(1, "\n", 1);
	return ;
}

void do_nl(int sig)
{
	if(sig == SIGUSR1)
		global_heredoc = 2;
	return ;
}

void no_nl(int sig)
{
	if(sig == SIGUSR2)
		global_heredoc = 0;
	return ;
}

void	sig_controler(int status)
{
	if (status == 0)
	{
		signal(SIGUSR1, SIG_IGN);
		signal(SIGUSR2, SIG_IGN);
		signal(SIGINT, str_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 1)
	{
		signal(SIGUSR1, SIG_IGN);
		signal(SIGUSR2, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (status == 2)
	{
		signal(SIGUSR1, do_nl);
		signal(SIGUSR2, no_nl);
		signal(SIGINT, new_line);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 3)
	{
		signal(SIGUSR1, SIG_IGN);
		signal(SIGUSR2, SIG_IGN);
		signal(SIGINT, sig_doc);
		signal(SIGQUIT, SIG_IGN);
	}
	return ;
}