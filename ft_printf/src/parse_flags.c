/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:05 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 12:21:54 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Credit to mlu for helping me with this and showing me the light that is
** ternary operators.  Holy shit, do they make this clusterfuck compact.
** Basically, this works by parsing the arguments, running under the assumption
** that there are indeed arguments to parse, and casts the arguments
** accordingly.  Need to make a printer for all the good casting that
** I'm doing.  Oh shit, I gotta call this the casting couch or something
** equally horrid.
*/

void	parse_hflag(va_list arg, int *i, const char *str, t_all *f)
{
	*i += 1;
	str[*i] == 'd' ? h_int_cast(arg, f) : 0;
	str[*i] == 'i' ? h_int_cast(arg, f) : 0;
	str[*i] == 'o' ? h_oct_cast(arg, f) : 0;
	str[*i] == 'x' ? h_lhex_cast(arg, f) : 0;
	str[*i] == 'X' ? h_hex_cast(arg, f) : 0;
	str[*i] == 'u' ? h_uint_cast(arg, f) : 0;
}

void	parse_hhflag(va_list arg, int *i, const char *str, t_all *f)
{
	*i += 2;
	str[*i] == 'd' ? hh_int_cast(arg, f) : 0;
	str[*i] == 'i' ? hh_int_cast(arg, f) : 0;
	str[*i] == 'o' ? hh_oct_cast(arg, f) : 0;
	str[*i] == 'x' ? hh_lhex_cast(arg, f) : 0;
	str[*i] == 'X' ? hh_hex_cast(arg, f) : 0;
	str[*i] == 'u' ? hh_uint_cast(arg, f) : 0;
}

void	parse_lflag(va_list arg, int *i, const char *str, t_all *f)
{
	*i += 1;
	str[*i] == 'd' ? l_int_cast(arg, f) : 0;
	str[*i] == 'i' ? l_int_cast(arg, f) : 0;
	str[*i] == 'o' ? l_oct_cast(arg, f) : 0;
	str[*i] == 'x' ? l_lhex_cast(arg, f) : 0;
	str[*i] == 'X' ? l_hex_cast(arg, f) : 0;
	str[*i] == 'u' ? l_uint_cast(arg, f) : 0;
	str[*i] == 'c' ? elsie_cast(arg, f) : 0;
	str[*i] == 's' ? loss_cast(arg, f) : 0;
}

void	parse_llflag(va_list arg, int *i, const char *str, t_all *f)
{
	*i += 2;
	str[*i] == 'd' ? ll_int_cast(arg, f) : 0;
	str[*i] == 'i' ? ll_int_cast(arg, f) : 0;
	str[*i] == 'o' ? ll_oct_cast(arg, f) : 0;
	str[*i] == 'x' ? ll_lhex_cast(arg, f) : 0;
	str[*i] == 'X' ? ll_hex_cast(arg, f) : 0;
	str[*i] == 'u' ? ll_uint_cast(arg, f) : 0;
}
