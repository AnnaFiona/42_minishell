/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:25:58 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:25:39 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(char *arr, long int n, int x)
{
	int		remain;
	char	i;

	while (n > 0)
	{
		remain = n % 10;
		n = n / 10;
		i = remain + '0';
		arr[x] = i;
		x--;
	}
	return (arr);
}

static int	how_many_digits(long int n)
{
	int	x;

	x = 0;
	while (n != 0)
	{
		n /= 10;
		x++;
	}
	return (x);
}

static char	*ft_minus(long int n)
{
	char	*arr;
	int		x;

	x = how_many_digits(n);
	if (n < 0)
		x++;
	arr = malloc(x + 1 * sizeof(char));
	if (!arr)
		return (0);
	arr[x] = '\0';
	x--;
	if (n < 0)
	{
		n *= -1;
		arr[0] = '-';
	}
	return (ft_convert (arr, n, x));
}

char	*ft_itoa(int n)
{
	char	*zero;

	if (n == 0)
	{
		zero = malloc(2 * sizeof(char));
		if (!zero)
			return (0);
		zero[0] = '0';
		zero[1] = 0;
		return (zero);
	}
	return (ft_minus(n));
}

/* int	main(void)
{
	printf ("%s", ft_itoa(2147483647 -1));
} */