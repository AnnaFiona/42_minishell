/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:48:48 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:26:40 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int i, size_t n)
{
	int		x;
	char	c;
	char	*str;

	str = s;
	c = i;
	x = 0;
	while (n > 0)
	{
		str[x] = c;
		x++;
		n--;
	}
	return (s);
}
/*
int	main(void)
{
	char c = '-';
	int x = 7;
	char für_mem[] = "replace this";
	char s[] = "replace this";
	ft_memset(s, c, x);
	memset(für_mem, c, x);
	printf("%p\n",s);
	printf("%p\n",für_mem);
}*/