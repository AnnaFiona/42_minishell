/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:35:31 by aplank            #+#    #+#             */
/*   Updated: 2023/02/06 18:36:49 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**is_there_a_nullbyte(char **arrarr, const char *s, int y)
{
	if (s[0] == '\0')
		arrarr[0] = (char *)0;
	else
		arrarr[y] = (char *)0;
	return (arrarr);
}

static char	**seperating(const char *s, char c, char **arrarr, int x)
{
	int	y;
	int	len;

	len = 0;
	y = 0;
	while (s[x])
	{
		if (s[x] != c)
		{
			while (s[x + len] != c && s[x + len])
				len++;
			arrarr[y] = ft_substr(s, x, len);
			x += len;
			len = 0;
			y++;
		}
		if (s[x] == 0)
			break ;
		x++;
	}
	return (is_there_a_nullbyte(arrarr, s, y));
}

char	**ft_split(char const *s, char c)
{
	int		x;
	int		y;
	char	**arrarr;

	if (!s)
		return (0);
	y = 0;
	x = 0;
	while (s[x] == c)
		x++;
	while (s[x])
	{
		if ((s[x] == c && s[x - 1] != c) || (s[x] != c && s[x + 1] == '\0'))
			y++;
		x++;
	}
	arrarr = malloc((y + 1) * sizeof(char *));
	if (!arrarr)
		return (0);
	x = 0;
	while (s[x] == c)
		x++;
	return (seperating(s, c, arrarr, x));
}

/* static char	**is_there_a_nullbyte(char **arrarr, const char *s, int y)
{
	if (s[0] == '\0')
		arrarr[0] = (char *)0;
	else
		arrarr[y] = (char *)0;
	return (arrarr);
}

static char	**seperating(const char *s, char c, char **arrarr, int x)
{
	int	y;
	int	len;

	len = 0;
	y = 0;
	while (s[x])
	{
		if (s[x] != c)
		{
			while (s[x + len] != c && s[x + len])
				len++;
			arrarr[y] = ft_substr(s, x, len);
			x += len;
			len = 0;
		}
		if (((s[x] == c && s[x - 1] != c) || (s[x] != c && s[x + 1] == '\0') || \
				s[x] == 0))
			y++;
		if (s[x] == 0)
			break ;
		x++;
	}
	return (is_there_a_nullbyte(arrarr, s, y));
}

char	**ft_split(char const *s, char c)
{
	int		x;
	int		y;
	char	**arrarr;

	if (!s)
		return (0);
	y = 0;
	x = 0;
	while (s[x] == c)
		x++;
	while (s[x])
	{
		if ((s[x] == c && s[x - 1] != c) || (s[x] != c && s[x + 1] == '\0'))
			y++;
		x++;
	}
	arrarr = malloc((y + 1) * sizeof(char *));
	if (!arrarr)
		return (0);
	x = 0;
	while (s[x] == c)
		x++;
	return (seperating(s, c, arrarr, x));
}

int	main(void)
{
	char arr[] = "ewjvniwepv";
	char **arrarr = ft_split(arr, ' ');
	printf("%s", arrarr[0]);
	printf("%s", arrarr[7000]);
} */
