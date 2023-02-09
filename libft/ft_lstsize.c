/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:42:32 by aplank            #+#    #+#             */
/*   Updated: 2022/10/21 15:48:09 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	x;

	x = 0;
	while (lst)
	{
		lst = lst->next;
		x++;
	}
	return (x);
}

/* int main()
{
    t_list  *first;
    t_list  *second;
    t_list  *third;

    third = ft_lstnew((void*)3);
    second = ft_lstnew((void*)2);
    second->next = third;
    first = ft_lstnew((void*)1);
    first->next = second;
	printf("%d", ft_lstsize(first));
} */