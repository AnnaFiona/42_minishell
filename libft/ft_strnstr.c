/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:08:21 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:27:58 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	y;

	x = 0;
	if (big == 0 && len == 0)
		return (0);
	if (little[0] == '\0')
		return ((char *)(big));
	while (big[x])
	{
		y = 0;
		while (big[x + y] == little[y] && big[x + y] != '\0' && x + y < len)
		{
			if (little[y + 1] == '\0')
				return ((char *)(&big[x]));
			y++;
		}
		x++;
	}
	return (0);
}

/* int	main(void)
{
    char arr1[] = "iuthutiughdff";
    char arr2[] = "";
    int x = 0;
    
    printf ("%s\n", ft_strnstr(arr1, arr2, x));
//    printf ("%d\n", strnstr(arr1, arr2, x));
} */
