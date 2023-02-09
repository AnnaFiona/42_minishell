/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:14 by aplank            #+#    #+#             */
/*   Updated: 2022/10/17 17:41:36 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (y < size && dst[y])
		y++;
	while ((y + x + 1) < size && src[x])
	{
		dst[y + x] = src[x];
		x++;
	}
	if (y < size)
		dst[y + x] = '\0';
	return (y + ft_strlen(src));
}
