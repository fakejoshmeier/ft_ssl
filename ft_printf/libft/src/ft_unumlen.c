/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unumlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:19:51 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/14 16:05:34 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_unumlen(unsigned int n, int base)
{
	int		len;
	long	nb;

	if (n == 0)
		return (1);
	len = 0;
	nb = (long)n;
	while (nb != 0)
	{
		len++;
		nb /= base;
	}
	return (len);
}
