/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:25:16 by aplank            #+#    #+#             */
/*   Updated: 2022/11/18 17:38:34 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_subfree(char *s, unsigned int start, size_t len)
{
	char	*substr;
	int		x;

	if (!s[start - 1])
	{
		free(s);
		return (NULL);
	}
	x = 0;
	if (start >= ft_gnl_strlen(s))
		len = 0;
	else if (ft_gnl_strlen(s + start) < len)
		len = ft_gnl_strlen(s + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	while (len > 0 && s[start])
	{
		substr[x++] = s[start++];
		len--;
	}
	substr[x] = '\0';
	free(s);
	return (substr);
}

char	*ft_subline(char *s, unsigned int start, size_t len)
{
	char	*substr;
	int		x;

	if (s[0] == '\0')
		return (NULL);
	x = 0;
	if (start >= ft_gnl_strlen(s))
		len = 0;
	else if (ft_gnl_strlen(s + start) < len)
		len = ft_gnl_strlen(s + start);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	while (len > 0 && s[start])
	{
		substr[x++] = s[start++];
		len--;
	}
	substr[x] = '\0';
	return (substr);
}

char	*ft_strmerge(char *s1, char const *s2)
{
	int		x;
	int		y;
	char	*str;

	if (!s1)
	{
		(s1 = malloc(1));
		s1[0] = '\0';
	}
	x = 0;
	y = 0;
	str = malloc((ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[x])
	{
		str[x] = s1[x];
		x++;
	}
	while (s2[y])
		str[x++] = s2[y++];
	free(s1);
	str[x] = '\0';
	return (str);
}

char	*read_file(int fd, char *file)
{
	char	*buf;
	int		check;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (ft_check(file) == 0)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check == -1)
		{
			free(buf);
			free(file);
			return (NULL);
		}
		if (check == 0)
			break ;
		buf[check] = '\0';
		file = ft_strmerge(file, buf);
	}
	free(buf);
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file[1024];
	char		*line;
	int			line_len;
	int			file_len;

	file_len = 0;
	line_len = 0;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (0);
	file[fd] = read_file(fd, file[fd]);
	if (!file[fd])
	{
		free(file[fd]);
		return (NULL);
	}
	while (file[fd][line_len] != '\n' && file[fd][line_len] != '\0')
		line_len++;
	while (file[fd][file_len] != '\0')
		file_len++;
	line = ft_subline(file[fd], 0, line_len + 1);
	file[fd] = ft_subfree(file[fd], line_len + 1, file_len);
	return (line);
}
