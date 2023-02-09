/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:30:56 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:28:22 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int x)
{
	if (x >= 65 && x <= 90)
		return (x += 32);
	return (x);
}
/*
int	main(void)
{
    char c = 'Z';
	printf("%c\n", ft_tolower(c));
    printf("%c\n", tolower(c));
}*/