/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulonglonglen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:19:51 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/14 16:05:21 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ulonglonglen(unsigned long long n, int base)
{
	int					len;
	unsigned long long	nb;

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
