/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:07:38 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:27:47 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		x;

	if (!s)
		return (0);
	x = 0;
	str = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!str)
		return (0);
	while (s[x])
	{
		str[x] = f(x, s[x]);
		x++;
	}
	str[x] = '\0';
	return (str);
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