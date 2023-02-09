/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:50:18 by aplank            #+#    #+#             */
/*   Updated: 2022/10/21 16:15:09 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
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