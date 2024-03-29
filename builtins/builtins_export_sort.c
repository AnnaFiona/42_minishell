#include "../minishell.h"

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

	i = 0;
	while (matrix[i])
	{
		x = i + 1;
		while (matrix[x])
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
	while (top != NULL)
	{
		ft_printf("declare -x ");
		ft_printf("%s", top->var);
		if (top->value)
			ft_printf("=\"%s\"", top->value);
		else if (top->equal == '=')
			ft_printf("=\"\"");
		ft_printf("\n");
		top = top->next;
	}
	return ;
}

void	sort_env(t_data *data, char **env)
{
	char	**matrix;

	matrix = save_envp(env);
	strcmp_sort(matrix);
	matrix_to_list(data, matrix);
	print_export_list(data->env_list);
	free_env_list(&data->env_list);
	free_double_array(matrix);
	return ;
}
