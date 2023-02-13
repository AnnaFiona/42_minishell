
#include "minishell.h"

void	ft_pwd(void)
{
	char	buf[100];

	getcwd(buf, 100);
	ft_printf("%s\n", buf);
	return ;
}

void	ft_cd(t_data *data)
{
	if(data->args[2] && data->args[2][0] == '|')
		return ;
	else if(data->args[1] == NULL)
		chdir(getenv("HOME"));
	else if(data->args[2])
		ft_printf("cd: too many arguments\n");
	else if(chdir(data->args[1]))
		perror("Error ");
	return ;
}

void	change_dir(t_data *data)
{
	if (ft_strncmp(data->args[0], "cd", 3) == 0)
		ft_cd(data);
	else if (ft_strncmp(data->args[0], "pwd", 3) == 0)
	 	ft_pwd();
	return ;
}