/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upper_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:27:21 by aplank            #+#    #+#             */
/*   Updated: 2022/11/02 15:18:23 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_upper_hexa(unsigned int n)
{
	char	*nbr;
	int		len;
	int		i;

	i = 0;
	nbr = ft_hexa_itoa(n);
	while (nbr[i])
	{
		nbr[i] = ft_toupper(nbr[i]);
		i++;
	}
	len = ft_string(nbr);
	free(nbr);
	return (len);
}
