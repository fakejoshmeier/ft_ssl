/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:52:12 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 21:36:25 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_base_fd(unsigned int n, unsigned int base, int fd)
{
	int		p;
	char	*c;

	p = 1;
	c = "0123456789ABCDEFHIJKLMNOPQRSTUVWXYZ";
	while ((n / p) >= base)
		p *= base;
	while (p > 0)
	{
		ft_putchar_fd(c[(n / p) % base], fd);
		p /= base;
	}
}
