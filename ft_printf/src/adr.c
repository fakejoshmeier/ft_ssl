/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 19:47:02 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 20:24:52 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putadr(unsigned long n, t_all *f)
{
	if (n > 15)
	{
		putadr((n / 16), f);
		putadr((n % 16), f);
	}
	else if (n < 10)
	{
		f->adr += 1;
		ft_putchar(n + '0');
	}
	else
	{
		n == 10 ? ft_putchar('a') : 0;
		n == 11 ? ft_putchar('b') : 0;
		n == 12 ? ft_putchar('c') : 0;
		n == 13 ? ft_putchar('d') : 0;
		n == 14 ? ft_putchar('e') : 0;
		n == 15 ? ft_putchar('f') : 0;
		f->adr += 1;
	}
}

void	address(va_list arg, t_all *f)
{
	void			*output;
	unsigned long	adr;

	output = va_arg(arg, void*);
	adr = (unsigned long)(output);
	write(1, "0x", 2);
	f->adr += 2;
	putadr(adr, f);
}

void	ntame(va_list arg, t_all *f)
{
	int		skip;

	skip = va_arg(arg, int);
	ft_putnbr(f->adr);
	f->adr += (ft_numlen(f->adr, 10));
	f->adr += (ft_numlen(skip, 10));
}
