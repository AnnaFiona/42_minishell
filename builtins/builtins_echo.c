#include "../minishell.h"

static int	is_flag(char *second_com)
{
	int	x;

	x = 1;
	if (second_com == NULL)
		return (-1);
	if (second_com[0] != '-')
		return (1);
	while (second_com[x])
	{
		if (second_com[x] != 'n')
			return (1);
		x++;
	}
	return (0);
}

void	ft_echo(t_child *kid)
{
	char	n;
	int		y;

	y = 1;
	n = '+';
	if (is_flag(kid->commands[1]) == 0)
	{
		n = '-';
		y++;
	}
	while (kid->commands[y])
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
