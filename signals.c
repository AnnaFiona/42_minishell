
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
	g_in_fd_copy = dup(STDIN_FILENO);
	close (STDIN_FILENO);
	return ;
}

void	nl_parrent(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	return ;
}

void	sig_controler(int status)
{
	if (status == SIG_DEFAULT)
	{
		signal(SIGINT, str_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == SIG_KID)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (status == SIG_PARRENT)
	{
		signal(SIGINT, nl_parrent);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == SIG_HEREDOC)
	{
		signal(SIGINT, sig_doc);
		signal(SIGQUIT, SIG_IGN);
	}
	return ;
}
