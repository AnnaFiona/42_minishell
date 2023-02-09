/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:25:20 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:26:05 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*z;

	z = s;
	if (c == 0 && n == 0)
		return (0);
	while (n > 0)
	{
		if (*z == (char)(c))
			return ((void *)(z));
		z++;
		n--;
	}
	return (0);
}

/* int	main(void)
{
	char str[] = {1, 32, 4, 43, 5};
	printf("%p\n", ft_memchr(str, 0, 8));
	printf("%p\n", memchr(str, 0, 8));
} */