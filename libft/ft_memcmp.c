/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:14:49 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:26:13 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		x;
	char	*z1;
	char	*z2;

	z1 = (char *)s1;
	z2 = (char *)s2;
	x = 0;
	while (n > 0)
	{
		if (z1[x] != z2[x])
		{
			if (z1[x] >= 0 && z2[x] >= 0)
				return (z1[x] - z2[x]);
			else
				return (z2[x] - z1[x]);
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