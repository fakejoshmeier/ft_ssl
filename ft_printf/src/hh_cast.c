/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hh_cast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:59:06 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 22:12:07 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hh_int_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	short			output;

	output = (char)va_arg(arg, void*);
	prec_pad = sign_prec_parse((long long)output, f);
	width_pad = sign_width_parse((long long)output, f);
	prefix = sign_prefix_parse((int)output, f);
	if (f->dash == 1)
	{
		ft_putstr(prefix);
		ft_putstr(prec_pad);
		ft_putnbrf((int)output);
		ft_putstr(width_pad);
	}
	else
	{
		f->zero == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prefix);
		f->zero == 1 && f->prec_flag == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prec_pad);
		ft_putnbrf((int)output);
	}
	supa_free(prec_pad, width_pad, prefix);
}

void	hh_oct_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	unsigned char	output;

	output = (unsigned char)va_arg(arg, void*);
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

void	hh_hex_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	unsigned char	output;

	output = (unsigned char)va_arg(arg, void*);
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

void	hh_lhex_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	unsigned char	output;

	output = (unsigned char)va_arg(arg, void*);
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

void	hh_uint_cast(va_list arg, t_all *f)
{
	char			*prec_pad;
	char			*width_pad;
	char			*prefix;
	unsigned char	output;

	output = (unsigned char)va_arg(arg, void*);
	prec_pad = prec_parse((unsigned long long)output, f, 10);
	width_pad = width_parse((unsigned long long)output, f, 10);
	prefix = prefix_parse((unsigned int)output, 10, 0, f);
	if (f->dash == 1)
	{
		ft_putstr(prefix);
		ft_putstr(prec_pad);
		ft_putunbr_base((unsigned int)output, 10);
		ft_putstr(width_pad);
	}
	else
	{
		f->zero == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prefix);
		f->zero == 1 && f->prec_flag == 0 ? ft_putstr(width_pad) : 0;
		ft_putstr(prec_pad);
		ft_putunbr_base((unsigned int)output, 10);
	}
	supa_free(prec_pad, width_pad, prefix);
}
