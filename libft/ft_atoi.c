/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:35:26 by aplank            #+#    #+#             */
/*   Updated: 2022/11/02 16:06:43 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_this_plees(long long int i, long long int m, int y)
{
	if (y > 19 && m == -1)
		return (0);
	if (y > 19)
		return (-1);
	return (i * m);
}

int	ft_atoi(const char *nptr)
{
	long long int	m;
	long long int	i;
	int				x;
	int				y;

	y = 0;
	x = 0;
	i = 0;
	m = 1;
	while (nptr[x] == ' ' || (nptr[x] >= 9 && nptr[x] <= 13))
		x++;
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		if (nptr[x] == '-')
			m *= -1;
		x++;
	}
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		i = i * 10 + (nptr[x] - 48);
		x++;
		if (i != 0)
			y++;
	}
	return (return_this_plees (i, m, y));
}
/*
int	main(void)
{
	char	arr[] = "    1";
	
	printf("%i\n", ft_atoi(arr));
	printf("%i\n", atoi(arr));
	return (0);
}*/