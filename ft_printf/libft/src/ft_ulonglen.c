/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulonglen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:19:51 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/14 16:11:49 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ulonglen(unsigned long n, int base)
{
	int				len;
	unsigned long	nb;

	if (n == 0)
		return (1);
	len = 0;
	nb = n;
	while (nb != 0)
	{
		len++;
		nb /= base;
	}
	return (len);
}
