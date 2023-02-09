/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lower_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:24:27 by aplank            #+#    #+#             */
/*   Updated: 2022/11/02 15:17:29 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lower_hexa(unsigned int n)
{
	char	*nbr;
	int		len;

	nbr = ft_hexa_itoa(n);
	len = ft_string(nbr);
	free(nbr);
	return (len);
}
