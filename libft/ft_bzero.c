/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:04 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:24:10 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int		x;
	char	*str;

	str = s;
	x = 0;
	while (n > 0)
	{
		str[x] = '\0';
		x++;
		n--;
	}
}
/*
int	main(void)
{
	int x = 2;
	char for_original[] = "replace this";
	char s[] = "replace this";
	ft_bzero(s, x);
	bzero(for_original, x);
	printf("%s\n",s);
	printf("%s\n",for_original);
}*/