#include "../minishell.h"

void	ft_echo(t_child *kid)
{
	char	n;
	int		y;

	y = 1;
	n = '+';
	if (ft_strcmp(kid->commands[1], "-n") == 0)
	{
		n = '-';
		y++;
	}
	while(kid->commands[y])
	{
		ft_putstr_fd(kid->commands[y], 1);
		y++;
		if (kid->commands[y] == NULL)
			break ;
		write(1, " ", 1);
	}
	if (n == '-')
	{
		return ;
	}
	write(1, "\n", 1);
	return ;
}
