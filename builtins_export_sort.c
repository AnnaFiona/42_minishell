#include "minishell.h"

void	ft_swap_str(char **s1, char **s2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup(*s1);
	tmp2 = ft_strdup(*s2);
	free(*s1);
	free(*s2);
	*s1 = tmp2;
	*s2 = tmp1;
	return ;
}

void	strcmp_sort(char **matrix)
{
	int	i;
	int	x;
	int	len;

	i = 0;
	len = size_2d(matrix);
	while (i < len)
	{
		x = i + 1;
		while (x < len)
		{
			if (ft_strcmp(matrix[i], matrix[x]) > 0)
				ft_swap_str(&matrix[i], &matrix[x]);
			x++;
		}
		i++;
	}
	return ;
}

void	print_export_list(t_env_list *top)
{
	while(top != NULL)
	{
		ft_printf("declare -x ");
		ft_printf("%s=\"%s\"\n", top->var, top->value);
		top = top->next;
	}
	return ;
}

void	sort_env(t_data *data, char **env)
{
	t_env_list *tmp;
	char **matrix;

	tmp = NULL;
	matrix = save_envp(env);
	strcmp_sort(matrix);
	matrix_to_list(data, matrix, &tmp);
	print_export_list(tmp);
	free_env_list(&tmp);
	free_double_array(matrix);
	return ;
}