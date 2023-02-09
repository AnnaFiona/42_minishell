/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:29:35 by aplank            #+#    #+#             */
/*   Updated: 2022/11/02 15:19:22 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pointer(unsigned long int n)
{
	char	*nbr;
	int		len;

	if (!n)
		return (write(1, "(nil)", 5));
	nbr = ft_hexa_itoa(n);
	write(1, "0x", 2);
	len = ft_string(nbr);
	len += 2;
	free(nbr);
	return (len);
}
