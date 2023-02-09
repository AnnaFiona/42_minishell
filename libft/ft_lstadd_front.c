/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:08:19 by aplank            #+#    #+#             */
/*   Updated: 2022/10/21 14:42:59 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/* int main()
{
    t_list  *first;
    t_list  *second;
    t_list  *third;
    t_list  *new;

    first = ft_lstnew(1);
    first->next = second;
    second = ft_lstnew(2);
    second->next = third;
    third = ft_lstnew(3);
    new = ft_lstnew(-1);
    ft_lstadd_front(&first, &new);
} */