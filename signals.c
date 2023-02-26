
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

void	heredoc_nl_switch(int sig)
{
	if (sig == SIGINT && global_heredoc == 0)
		write(1, "\n", 1);
	else if (sig == SIGUSR1)
		global_heredoc = 2;
	else if (sig == SIGUSR2)
		global_heredoc = 0;
	return ;
}

void	main_after_fork(void)
{
	signal(SIGUSR1, heredoc_nl_switch);
	signal(SIGUSR2, heredoc_nl_switch);
	signal(SIGINT, heredoc_nl_switch);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

void	sig_controler(int status)
{
	if (status == SIG_DEFAULT)
	{
		signal(SIGUSR1, SIG_IGN);
		signal(SIGUSR2, SIG_IGN);
		signal(SIGINT, str_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == SIG_KID)
	{
		signal(SIGUSR1, SIG_IGN);
		signal(SIGUSR2, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (status == SIG_PARRENT)
		main_after_fork();
	else if (status == SIG_HEREDOC)
	{
		signal(SIGUSR1, SIG_IGN);
		signal(SIGUSR2, SIG_IGN);
		signal(SIGINT, sig_doc);
		signal(SIGQUIT, SIG_IGN);
	}
	return ;
}
