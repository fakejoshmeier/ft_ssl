/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prixfixe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:56:38 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 22:10:33 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*prefix_parse(unsigned int outpu, int base, int caps, t_all *f)
{
	char	*new;

	if (base == 16 && outpu != 0 && f->hash == 1)
	{
		new = ft_strnew(2);
		new[0] = '0';
		new[1] = caps == 1 ? 'X' : 'x';
		f->adr += 2;
	}
	else if (base == 8 && outpu != 0 && f->hash == 1)
	{
		new = ft_strnew(1);
		new[0] = '0';
		f->adr += 1;
	}
	else
		new = NULL;
	return (new);
}

char	*sign_prefix_parse(int output, t_all *f)
{
	char	*new;

	if (f->spess == 1 && output >= 0)
	{
		new = ft_strnew(1);
		new[0] = ' ';
		f->adr += 1;
	}
	else if (f->plus == 1 && output >= 0)
	{
		new = ft_strnew(1);
		new[0] = '+';
		f->adr += 1;
	}
	else if (output < 0)
	{
		new = ft_strnew(1);
		new[0] = '-';
		f->adr += 1;
	}
	else
		new = NULL;
	return (new);
}
