/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:42:25 by aplank            #+#    #+#             */
/*   Updated: 2022/11/02 15:19:45 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '%')
				len += write(1, "%", 1);
			else if (!(str[i] == 0))
				len += ft_redirecting(str[i], args);
		}
		else if (!(str[i] == 0))
			len += write(1, &str[i], 1);
		if (!(str[i] == 0))
			i++;
	}
	va_end(args);
	return (len);
}
