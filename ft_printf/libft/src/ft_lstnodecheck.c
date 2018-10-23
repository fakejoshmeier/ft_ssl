/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnodecheck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 23:00:18 by jmeier            #+#    #+#             */
/*   Updated: 2017/10/13 23:27:05 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstnodecheck(t_list *l1, t_list *l2)
{
	t_list	*l2_start;

	l2_start = l2;
	while (l1)
	{
		while (l2)
		{
			if (l1 == l2)
				return (1);
			l2 = l2->next;
		}
		l2 = l2_start;
		l1 = l1->next;
	}
	return (0);
}
