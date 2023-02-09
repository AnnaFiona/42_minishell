/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:12:34 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:27:23 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	x;

	x = 0;
	if (s)
	{
		while (s[x])
		{
			f(x, &s[x]);
			x++;
		}
	}
}

/* char	ttolower(int x, char c)
{
	if (c >= 65 && c <= 90)
		return (c += x);
	return (c);
}

int main ()
{
    printf("%s\n", ft_strmapi("kjghg", ttolower(-32, 'g')));
} */