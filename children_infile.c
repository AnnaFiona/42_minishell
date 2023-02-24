#include "minishell.h"

void	search_for_infile(t_data *data, t_child *kid)
{
	int	y;

	y = 0;
	while(kid->commands[y])
	{
		/* if (ft_strcmp(kid->commands[y], "<") == 0 && kid->in_quotes[y] != 'q')
		{
			is_it_a_token(data, kid, kid->commands, y + 1);
			open_outfile(data, kid, kid->commands[y + 1], 0);
			cut_token(kid, y);
			y--;
		} */
		if (ft_strcmp(kid->commands[y], "<<") == 0 && kid->in_quotes[y] != 'q')
		{
			heredoc(data, kid);
			y--;
		}
		y++;
	}
	return ;
}