/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_cast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:59:06 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 22:11:52 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	h_int_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	short			output;

	output = (short)va_arg(arg, void*);
	prec_pad = sign_prec_parse((long long)output, f);
	width_pad = sign_width_parse((long long)output, f);
	prefix = sign_prefix_parse((int)output, f);
	if (f->dash == 1)
	{
		ft_putstr(prefix);
		ft_putstr(prec_pad);
		ft_putnbrf(output);
		ft_putstr(width_pad);
	}
	else
	{
		f->zero == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prefix);
		f->zero == 1 && f->prec_flag == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prec_pad);
		ft_putnbrf(output);
	}
	supa_free(prec_pad, width_pad, prefix);
}

void	h_oct_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	unsigned short	output;

	output = (unsigned short)va_arg(arg, void*);
	prec_pad = prec_parse((unsigned long long)output, f, 8);
	width_pad = width_parse((unsigned long long)output, f, 8);
	prefix = prefix_parse((unsigned int)output, 8, 0, f);
	if (f->dash == 1)
	{
		ft_putstr(prefix);
		ft_putstr(prec_pad);
		ft_putoct((unsigned long long)output);
		ft_putstr(width_pad);
	}
	else
	{
		f->zero == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prefix);
		f->zero == 1 && f->prec_flag == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prec_pad);
		ft_putoct((unsigned long long)output);
	}
	supa_free(prec_pad, width_pad, prefix);
}

void	h_hex_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	unsigned short	output;

	output = (unsigned short)va_arg(arg, void*);
	prec_pad = prec_parse((unsigned long long)output, f, 16);
	width_pad = width_parse((unsigned long long)output, f, 16);
	prefix = prefix_parse((unsigned int)output, 16, 1, f);
	if (f->dash == 1)
	{
		ft_putstr(prefix);
		ft_putstr(prec_pad);
		ft_puthex((unsigned long long)output);
		ft_putstr(width_pad);
	}
	else
	{
		f->zero == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prefix);
		f->zero == 1 && f->prec_flag == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prec_pad);
		ft_puthex((unsigned long long)output);
	}
	supa_free(prec_pad, width_pad, prefix);
}

void	h_lhex_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	unsigned short	output;

	output = (unsigned short)va_arg(arg, void*);
	prec_pad = prec_parse((unsigned long long)output, f, 16);
	width_pad = width_parse((unsigned long long)output, f, 16);
	prefix = prefix_parse((unsigned int)output, 16, 0, f);
	if (f->dash == 1)
	{
		ft_putstr(prefix);
		ft_putstr(prec_pad);
		ft_putlhex((unsigned long long)output);
		ft_putstr(width_pad);
	}
	else
	{
		f->zero == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prefix);
		f->zero == 1 && f->prec_flag == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prec_pad);
		ft_putlhex((unsigned long long)output);
	}
	supa_free(prec_pad, width_pad, prefix);
}

void	h_uint_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	unsigned short	output;

	output = (unsigned short)va_arg(arg, void*);
	prec_pad = prec_parse((unsigned long long)output, f, 10);
	width_pad = width_parse((unsigned long long)output, f, 10);
	prefix = prefix_parse((unsigned int)output, 10, 0, f);
	if (f->dash == 1)
	{
		ft_putstr(prefix);
		ft_putstr(prec_pad);
		ft_putunbr_base(output, 10);
		ft_putstr(width_pad);
	}
	else
	{
		f->zero == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prefix);
		f->zero == 1 && f->prec_flag == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prec_pad);
		ft_putunbr_base(output, 10);
	}
	supa_free(prec_pad, width_pad, prefix);
}
