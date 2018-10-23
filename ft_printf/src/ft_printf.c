/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:20:44 by jmeier            #+#    #+#             */
/*   Updated: 2018/02/16 16:22:04 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Accounts for a lack of flags, working as putstr otherwise.  All of
** the initial parsing functions are placed here, so as to make it more compact
** and easy to follow.  Since there are 5 types of cast that need to be
** made per set of flags, all of the various flag types, e.g. -ll, -h, etc.,
** will have their own functions, titled along the lines of hh_cast or such.
** Nonprintable characters are taken care of immediately, as I like not having
** to think about them in a separate function.  parse_extra_flags is written
** as it is to provide space for any future additions to my code.
** Credit to mlu for showing me the light of ternary operators and how they
** just werk for a project like this.
*/

void	reset_struct(t_all *f)
{
	f->dash = 0;
	f->zero = 0;
	f->plus = 0;
	f->hash = 0;
	f->spess = 0;
	f->width = 0;
	f->prec = 0;
	f->prec_flag = 0;
	f->wid_flag = 0;
}

void	suite(const char *str, int *i, va_list arg, t_all *f)
{
	*i += 1;
	parse_format(str, i, f);
	parse_width(str, i, arg, f);
	parse_prec(str, i, arg, f);
	parse_flags(arg, i, str, f);
	reset_struct(f);
}

void	parse_escape(int *i, const char *str, t_all *f)
{
	*i += 1;
	str[*i] == 'a' ? ft_putchar('\a') : 0;
	str[*i] == '\\' ? ft_putchar('\\') : 0;
	str[*i] == 'b' ? ft_putchar('\b') : 0;
	str[*i] == 'r' ? ft_putchar('\r') : 0;
	str[*i] == '"' ? ft_putchar('\"') : 0;
	str[*i] == 'f' ? ft_putchar('\f') : 0;
	str[*i] == 't' ? ft_putchar('\t') : 0;
	str[*i] == 'n' ? ft_putchar('\n') : 0;
	str[*i] == '0' ? ft_putchar('\0') : 0;
	str[*i] == '\'' ? ft_putchar('\'') : 0;
	str[*i] == 'v' ? ft_putchar('\v') : 0;
	str[*i] == '?' ? ft_putchar('\?') : 0;
	f->adr += 1;
}

void	parse_flags(va_list arg, int *i, const char *str, t_all *f)
{
	str[*i] == 'd' ? int_cast(arg, f) : 0;
	str[*i] == 'i' ? int_cast(arg, f) : 0;
	str[*i] == 'o' ? oct_cast(arg, f) : 0;
	str[*i] == 'x' ? lhex_cast(arg, f) : 0;
	str[*i] == 'X' ? hex_cast(arg, f) : 0;
	str[*i] == 'u' ? uint_cast(arg, f) : 0;
	str[*i] == 'c' ? char_cast(arg, f) : 0;
	str[*i] == 's' ? str_cast(arg, f) : 0;
	str[*i] == '%' ? percent(f) : 0;
	str[*i] == 'j' ? parse_jflag(arg, i, str, f) : 0;
	str[*i] == 'z' ? parse_zflag(arg, i, str, f) : 0;
	str[*i] == 'p' ? address(arg, f) : 0;
	(str[*i] == 'h' && str[*i + 1] != 'h') ? parse_hflag(arg, i, str, f) : 0;
	(str[*i] == 'h' && str[*i + 1] == 'h') ? parse_hhflag(arg, i, str, f) : 0;
	(str[*i] == 'l' && str[*i + 1] != 'l') ? parse_lflag(arg, i, str, f) : 0;
	(str[*i] == 'l' && str[*i + 1] == 'l') ? parse_llflag(arg, i, str, f) : 0;
	str[*i] == 'O' ? l_oct_cast(arg, f) : 0;
	str[*i] == 'D' ? l_int_cast(arg, f) : 0;
	str[*i] == 'U' ? l_uint_cast(arg, f) : 0;
	str[*i] == 'C' ? elsie_cast(arg, f) : 0;
	str[*i] == 'S' ? loss_cast(arg, f) : 0;
	str[*i] == 'n' ? ntame(arg, f) : 0;
}

int		ft_printf(const char *format, ...)
{
	va_list	arg;
	t_all	*f;
	int		pos;

	ASSERT(format);
	va_start(arg, format);
	pos = -1;
	f = (t_all *)ft_memalloc(sizeof(t_all));
	while (format[++pos])
	{
		if (format[pos] == '%')
			suite(format, &pos, arg, f);
		else if (format[pos] == '\\')
			parse_escape(&pos, format, f);
		else
		{
			ft_putchar(format[pos]);
			f->adr += 1;
		}
	}
	free(f);
	va_end(arg);
	return (0);
}
