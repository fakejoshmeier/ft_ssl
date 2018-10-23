/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 02:41:40 by jmeier            #+#    #+#             */
/*   Updated: 2018/02/16 16:22:22 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		isflag(char c)
{
	if (c == ' ' || c == '-' || c == '+' || c == '#' || c == '0' || c == '.')
		return (1);
	return (0);
}

void	percent(t_all *f)
{
	ft_putchar('%');
	f->adr += 1;
}

void	parse_width(const char *str, int *i, va_list arg, t_all *f)
{
	if (!(ft_isdigit(str[*i])) && str[*i] != '*')
		return ;
	f->wid_flag = 1;
	if (str[*i] == '*')
	{
		f->width = va_arg(arg, int);
		*i += 1;
		return ;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		f->width = f->width * 10 + str[*i] - '0';
		*i += 1;
	}
}

void	parse_prec(const char *str, int *i, va_list arg, t_all *f)
{
	if (str[*i] != '.')
		return ;
	f->prec_flag = 1;
	*i += 1;
	if (str[*i] == '*')
	{
		f->prec = va_arg(arg, int);
		*i += 1;
		return ;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		f->prec = f->prec * 10 + str[*i] - '0';
		*i += 1;
	}
}

void	parse_format(const char *str, int *i, t_all *f)
{
	while (isflag(str[*i]))
	{
		str[*i] == '+' ? f->plus = 1 : 0;
		str[*i] == '-' ? f->dash = 1 : 0;
		str[*i] == '#' ? f->hash = 1 : 0;
		str[*i] == '0' ? f->zero = 1 : 0;
		str[*i] == ' ' ? f->spess = 1 : 0;
		*i += 1;
	}
}
