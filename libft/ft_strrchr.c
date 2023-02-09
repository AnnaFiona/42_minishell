/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:57:15 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:28:03 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	x;

	x = 0;
	while (*s != '\0')
	{
		s++;
		x++;
	}
	while (x >= 0)
	{
		if (*s == (char)(c))
			return ((char *)(s));
		s--;
		x--;
	}
	return (0);
}

/* int	main(void)
{
    char c = 0;
    char str[] = "there is a nyancat under your bed";
	printf("%s\n", ft_strrchr(str, c));
    printf("%s\n", strrchr(str, c));
} */