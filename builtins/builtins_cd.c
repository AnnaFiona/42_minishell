
#include "../minishell.h"

static int	remove_end_malloc(char *str, char c)
{
	int		len;

	len = ft_strlen(str);
	while ((len) > 0)
	{
		if (str[len] == c)
			break ;
		len--;
	}
	return (len);
}

static void	remove_end(char *str, char c)
{
	int		i;
	char	*tmp;
	int		len;

	if (!str)
		return ;
	i = 0;
	len = remove_end_malloc(str, c);
	tmp = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	free(str);
	str = tmp;
	return ;
}

static void	save_pwd(t_data *data, char *pwd, char *path)
{
	char	*new_path;

	if (ft_strcmp(path, ".."))
		is_dublicate(data, pwd, path);
	else
	{
		new_path = ft_getenv(data, "PWD");
		remove_end(new_path, '/');
		is_dublicate(data, pwd, new_path);
	}
	env_list_to_matrix(data);
	return ;
}

int	ft_cd(t_data *data, char *path)
{
	char	*old_pwd;

	if (!path)
	{
		path = ft_getenv(data, "HOME");
		if (!path)
		{
			ft_printf("minishell: cd: HOME not set\n");
			return (0);
		}
	}
	if (chdir(path))
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		//free(path);
		return (0);
	}
	old_pwd = ft_getenv(data, "PWD");
	save_pwd(data, "OLDPWD", old_pwd);
	save_pwd(data, "PWD", path);
	//free(path);
	free(old_pwd);
	return (0);
}
