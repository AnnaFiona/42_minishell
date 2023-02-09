/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:40:36 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:26:23 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int			x;
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	x = 0;
	if (dest == 0 && src == 0)
	{
		return (dest);
	}
	while (n > 0)
	{
		d[x] = s[x];
		x++;
		n--;
	}
	return (dest);
}
/*
int	main(void)
{
    char arr1[] = "please work";
    char arr2[] = "aaaaaaaaaaaaaaaa";
    char *dest = arr2;
    char *src = arr1;
    
    ft_memcpy(dest, src, 7);
    printf ("%p\n", dest);
}*/
/*
int	main(void)
{
    char    src[] = "Willkommen";
    char    dest[] = "ill";

//    char    *destptr = ft_memcpy(dest, src, strlen(src) + 1);
    char    *destptr = memcpy(dest, src, strlen(src) + 1);

    printf("src: %s\n", src);
    printf("dest: %s\n", dest);

    printf("destptr: %p\n", destptr);
    printf("       : %p\n", dest);
}*/