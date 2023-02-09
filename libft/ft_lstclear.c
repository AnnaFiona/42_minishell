/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aplank <aplank@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:23:04 by aplank            #+#    #+#             */
/*   Updated: 2022/10/24 12:08:46 by aplank           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*nxt;

	if (lst && del)
	{
		node = *lst;
		while (node)
		{
			nxt = node->next;
			ft_lstdelone(node, del);
			node = nxt;
		}
		*lst = NULL;
	}
}
