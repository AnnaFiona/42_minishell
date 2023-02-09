/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:30:17 by aplank            #+#    #+#             */
/*   Updated: 2022/11/02 15:17:50 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_redirecting(char str, va_list args)
{
	int	len;

	len = 0;
	if (str == 'c')
		len = ft_char(va_arg(args, int));
	else if (str == 's')
		len = ft_string(va_arg(args, char *));
	else if (str == 'p')
		len = ft_pointer((unsigned long int)(va_arg(args, void *)));
	else if (str == 'd' || str == 'i')
		len = ft_decimal_integer(va_arg(args, int));
	else if (str == 'u')
		len = ft_unsigned_decimal(va_arg(args, unsigned int));
	else if (str == 'x')
		len = ft_lower_hexa(va_arg(args, unsigned int));
	else if (str == 'X')
		len = ft_upper_hexa(va_arg(args, unsigned int));
	return (len);
}
