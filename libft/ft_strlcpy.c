/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:37:13 by aplank            #+#    #+#             */
/*   Updated: 2022/10/12 10:41:34 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	x;

	x = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[x] != '\0' && size - 1 > 0)
	{
		dst[x] = src[x];
		x++;
		size--;
	}
	dst[x] = '\0';
	return (ft_strlen(src));
}

/* int	main(void)
{
	char arr1[] = "please work";
	char arr2[] = "aaaaaaaaaaaaaaaa";
	char *dest = arr2;
	char *src = arr1;

	ft_memcpy(dest, src, 7);
	printf("%p\n", dest);
} */