/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlonglong.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:52:12 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 19:31:18 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlonglong(long long n, long long base, int fd)
{
	long long	p;
	char		*c;

	p = 1;
	c = "0123456789ABCDEFHIJKLMNOPQRSTUVWXYZ";
	while ((n / p) >= base || (n / p) <= -base)
		p *= base;
	while (p > 0)
	{
		ft_putchar_fd(c[(n / p) % base], fd);
		p /= base;
	}
}
