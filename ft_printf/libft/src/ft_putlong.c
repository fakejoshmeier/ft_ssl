/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:52:12 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 20:56:42 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlong(long n, long base, int fd)
{
	long	p;
	char	*c;

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
