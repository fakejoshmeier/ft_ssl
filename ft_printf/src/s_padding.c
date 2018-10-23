/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_padding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 05:10:43 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 20:56:28 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*sign_width_parse(long long output, t_all *f)
{
	char	*new;
	int		len;
	int		i;
	int		g;

	if (f->wid_flag == 0)
		return (NULL);
	g = ft_longlonglen(output, 10);
	i = g > f->prec ? g : f->prec;
	if ((f->spess == 1 && output >= 0) || (f->plus == 1 && output >= 0)
		|| output < 0)
		i += 1;
	len = f->width > i ? f->width - i : 0;
	new = ft_strnew(len);
	if (f->dash == 0 && f->prec_flag == 0 && f->zero == 1)
		ft_memset(new, '0', len);
	else
		ft_memset(new, ' ', len);
	f->adr += len;
	return (new);
}

char	*width_parse(unsigned long long output, t_all *f, int base)
{
	char	*new;
	int		len;
	int		i;

	if (f->wid_flag == 0)
		return (NULL);
	i = ft_ulonglonglen(output, base);
	i += f->hash == 1 ? 1 : 0;
	i += f->hash == 1 && base == 16 ? 1 : 0;
	len = f->width > i ? f->width - i : 0;
	new = ft_strnew(len);
	if (f->dash == 0 && f->prec_flag == 0 && f->zero == 1)
		ft_memset(new, '0', len);
	else
		ft_memset(new, ' ', len);
	f->adr += len;
	return (new);
}

char	*sign_prec_parse(long long output, t_all *f)
{
	char	*new;
	int		i;
	int		g;

	if (f->prec_flag == 0)
		return (NULL);
	g = ft_longlonglen(output, 10);
	f->adr += f->prec < g ? f->prec : g;
	if (f->prec > g)
	{
		i = f->prec - g;
		new = ft_strnew(i);
		ft_memset(new, '0', i);
		return (new);
	}
	return (NULL);
}

char	*prec_parse(unsigned long long output, t_all *f, int b)
{
	char	*new;
	int		i;
	int		g;

	if (f->prec_flag == 0)
		return (NULL);
	g = ft_ulonglonglen(output, b);
	f->adr += f->prec < g ? f->prec : g;
	if (f->prec > g)
	{
		i = f->prec - g;
		new = ft_strnew(i);
		ft_memset(new, '0', i);
		return (new);
	}
	return (NULL);
}
