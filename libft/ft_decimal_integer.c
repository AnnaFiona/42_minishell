/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_integer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:11:43 by aplank            #+#    #+#             */
/*   Updated: 2022/11/02 15:17:10 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_decimal_integer(int n)
{
	char	*nbr;
	int		len;

	nbr = ft_itoa(n);
	len = ft_string(nbr);
	free (nbr);
	return (len);
}
