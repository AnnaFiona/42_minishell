/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:36:35 by aplank            #+#    #+#             */
/*   Updated: 2022/11/23 16:25:19 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		x;
	int		y;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	x = 0;
	y = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[x])
	{
		str[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		str[x] = s2[y];
		x++;
		y++;
	}
	str[x] = '\0';
	return (str);
}
/*
int	main(void)
{
    char arr1[] = "";
    char arr2[] = "under your bed";
    
    printf ("%s\n", strjoin(arr1, arr2));
} */
