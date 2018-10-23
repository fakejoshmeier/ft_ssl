/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlonglong_lc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:52:12 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 21:34:31 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlonglong_lc(unsigned long long n, unsigned long long b, int fd)
{
	unsigned long long	p;
	char				*c;

	p = 1;
	c = "0123456789abcdefghijklmnopqrstuvwxyz";
	while ((n / p) >= b)
		p *= b;
	while (p > 0)
	{
		ft_putchar_fd(c[(n / p) % b], fd);
		p /= b;
	}
}
