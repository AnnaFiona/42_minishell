/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:33:34 by aplank            #+#    #+#             */
/*   Updated: 2022/10/21 17:48:37 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
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