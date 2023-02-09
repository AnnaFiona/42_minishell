/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:30:39 by aplank            #+#    #+#             */
/*   Updated: 2022/11/02 15:17:17 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(char *arr, unsigned long int n, int x)
{
	int		remain;
	char	i;

	while (n > 0)
	{
		remain = n % 16;
		n = n / 16;
		if (remain > 9)
			i = remain + 'W';
		else
			i = remain + '0';
		arr[x] = i;
		x--;
	}
	return (arr);
}

static int	how_many_digits(unsigned long int n)
{
	int	x;

	x = 0;
	while (n != 0)
	{
		n /= 16;
		x++;
	}
	return (x);
}

char	*ft_hexa_itoa(unsigned long int n)
{
	char	*zero;
	char	*arr;
	int		x;

	if (n == 0)
	{
		zero = malloc(2 * sizeof(char));
		if (!zero)
			return (0);
		zero[0] = '0';
		zero[1] = 0;
		return (zero);
	}
	x = how_many_digits(n);
	arr = malloc(x + 1 * sizeof(char));
	if (!arr)
		return (0);
	arr[x] = '\0';
	x--;
	return (ft_convert (arr, n, x));
}
