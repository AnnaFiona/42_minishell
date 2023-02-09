/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:49:46 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:27:10 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if ((char)c == '\0')
		return ((char *)(&s[ft_strlen(s)]));
	while (*s != '\0')
	{
		if (*s == (char)(c))
			return ((char *)(s));
		s++;
	}
	return (0);
}
/*
int	main(void)
{
	char c = 'Z';
	char str[] = "kfjdörunZdrönb";
	printf("%s\n", str);
	printf("%s\n", ft_strchr(str, c));
	printf("%s\n", str);
	printf("%s\n", strchr(str, c));
	printf("%s\n", str);
}*/