/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:29:56 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:28:12 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	beginning(char const *s1, char const *set)
{
	int	x;
	int	a;
	int	beg;

	beg = 0;
	x = 0;
	a = 1;
	while (a != 0)
	{
		a = 0;
		while (set[x])
		{
			while (s1[beg] == set[x])
			{
				beg++;
				a++;
			}
			x++;
		}
		x = 0;
	}
	return (beg);
}

static int	ending(char const *s1, char const *set)
{
	int	x;
	int	a;
	int	end;

	end = ft_strlen(s1) - 1;
	x = 0;
	a = 1;
	while (a != 0)
	{
		a = 0;
		while (set[x])
		{
			while (s1[end] == set[x])
			{
				end--;
				a++;
			}
			x++;
		}
		x = 0;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	beg;
	int	end;

	if (s1 == 0)
		return (0);
	beg = beginning(s1, set);
	end = ending(s1, set);
	return (ft_substr(s1, beg, (end - beg + 1)));
}

/* int main()
{
    char arr1[] = "calbsrtlocaa";
    char arr2[] = "ac";
    
    printf ("%s\n", ft_strtrim(arr1, arr2));
//    printf ("%d\n", strnstr(arr1, arr2, x));
} */