/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:49:05 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 12:23:40 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** These should cover all of the other flags that can be applied to the
** commands.
*/

void	parse_zflag(va_list arg, int *i, const char *str, t_all *f)
{
	*i += 1;
	str[*i] == 'd' ? z_int_cast(arg, f) : 0;
	str[*i] == 'i' ? z_int_cast(arg, f) : 0;
	str[*i] == 'o' ? z_oct_cast(arg, f) : 0;
	str[*i] == 'x' ? z_lhex_cast(arg, f) : 0;
	str[*i] == 'X' ? z_hex_cast(arg, f) : 0;
	str[*i] == 'u' ? z_uint_cast(arg, f) : 0;
}

void	parse_jflag(va_list arg, int *i, const char *str, t_all *f)
{
	*i += 1;
	str[*i] == 'd' ? j_int_cast(arg, f) : 0;
	str[*i] == 'i' ? j_int_cast(arg, f) : 0;
	str[*i] == 'o' ? j_oct_cast(arg, f) : 0;
	str[*i] == 'x' ? j_lhex_cast(arg, f) : 0;
	str[*i] == 'X' ? j_hex_cast(arg, f) : 0;
	str[*i] == 'u' ? j_uint_cast(arg, f) : 0;
}
