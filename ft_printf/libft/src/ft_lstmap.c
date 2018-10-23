/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:15:23 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/27 15:13:30 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*l1;
	t_list	*l2;

	l1 = f(lst);
	l2 = l1;
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		l1->next = f(lst);
		if (!l1->next)
		{
			free(l1->next);
			return (NULL);
		}
		l1 = l1->next;
	}
	return (l2);
}
