/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:48:47 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:31:06 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	x;

	x = 0;
	while ((s1[x] || s2[x]) && n > 0)
	{
		if (s1[x] != s2[x])
		{
			if (s1[x] >= 0 && s2[x] >= 0)
				return (s1[x] - s2[x]);
			else
				return (s2[x] - s1[x]);
		}
		x++;
		n--;
	}
	return (0);
}
/*
int	main(void)
{
    char arr1[] = "iuthtiughdff";
    char arr2[] = "iuthtiughdfftt";
    
    printf ("%d\n",ft_strncmp(arr1, arr2, 14));
    printf ("%d\n",strncmp(arr1, arr2, 14));
}*/
