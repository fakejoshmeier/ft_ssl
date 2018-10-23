/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 00:32:34 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 08:51:18 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex(unsigned long long n)
{
	if (n > 15)
	{
		ft_puthex(n / 16);
		ft_puthex(n % 16);
	}
	else if (n < 10)
		ft_putchar(n + '0');
	else
	{
		n == 10 ? ft_putchar('A') : 0;
		n == 11 ? ft_putchar('B') : 0;
		n == 12 ? ft_putchar('C') : 0;
		n == 13 ? ft_putchar('D') : 0;
		n == 14 ? ft_putchar('E') : 0;
		n == 15 ? ft_putchar('F') : 0;
	}
}
