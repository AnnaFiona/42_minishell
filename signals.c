
#include "minishell.h"

void	ctrl_c(int sig)
{
	if(sig != SIGINT)
		return ;
	exit(0);
	return ;
}

void	ctrl_d(int sig)
{
	if(sig == SIGQUIT)
		return;
}
