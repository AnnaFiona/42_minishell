/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:32:20 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:40:18 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putstr(char *str, int fd)
{
	while (*str != '\0')
	{
		write(fd, str, 1);
		str++;
	}
}

static void	ft_rev_int_tab(char *tab, int size, int fd)
{
	char	*a;
	char	*b;
	char	temp;
	int		counter;

	a = tab;
	b = tab + (size - 1);
	counter = size / 2;
	while (counter > 0)
	{
		temp = *a;
		*a = *b;
		*b = temp;
		a++;
		b--;
		counter--;
	}
	ft_putstr(tab, fd);
}

static void	ft_negative(int n, int fd)
{
	char	arr[11];
	int		x;
	int		remain;
	char	i;

	x = 0;
	if (n == -2147483648)
	{
		n = -214748364;
		arr[x] = '8';
		x++;
	}
	n = n * -1;
	while (n > 0)
	{
		remain = n % 10;
		n = n / 10;
		i = remain + '0';
		arr[x] = i;
		x++;
	}
	arr[x] = '-';
	x++;
	arr[x] = '\0';
	ft_rev_int_tab(arr, x, fd);
}

static void	ft_positive(int n, int fd)
{
	char	arr[10];
	int		x;
	int		remain;
	char	i;

	x = 0;
	while (n > 0)
	{
		remain = n % 10;
		n = n / 10;
		i = remain + '0';
		arr[x] = i;
		x++;
	}
	arr[x] = '\0';
	ft_rev_int_tab(arr, x, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	z;

	z = '0';
	if (n == 0)
		write(fd, &z, 1);
	else if (n < 0)
		ft_negative(n, fd);
	else
		ft_positive(n, fd);
}
