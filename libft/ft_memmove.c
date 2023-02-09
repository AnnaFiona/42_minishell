/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:54:57 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:26:29 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*temp;
	char	*small;

	small = (char *)dest;
	temp = (char *)src;
	if (src < dest)
	{
		while (n--)
			small[n] = temp[n];
	}
	else
		ft_memcpy(dest, temp, n);
	return (dest);
}
/*
int	main(void)
{
    char arr1[] = "please work";
    char arr2[] = "aaaaaaaaaaaaaaaa";
    char *dest = arr2;
    char *src = arr1;
    
    ft_memmove(dest, src, 7);
    printf ("%s\n", dest);
}*/
/*
int	main(void)
{
    char    src[] = "Willkommen";
    char    dest[] = "ill";

    char    *destptr = memmove(dest, src, 10);
//    char    *destptr = memcpy(dest, src, strlen(src) + 1);

    printf("src: %s\n", src);
    printf("dest: %s\n", dest);

    printf("destptr: %s\n", destptr);
    printf("       : %s\n", dest);
}*/