/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:22:04 by aplank            #+#    #+#             */
/*   Updated: 2022/11/15 15:04:22 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnl_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (*s)
	{
		s++;
		x++;
	}
	return (x);
}

int	ft_check(char *file)
{
	int	i;

	i = 0;
	if (!file)
		return (0);
	while (file[i])
	{
		if (file[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
