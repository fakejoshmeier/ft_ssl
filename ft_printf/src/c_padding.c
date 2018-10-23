/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_padding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 12:55:47 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 05:45:13 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_prec(char output, t_all *f)
{
	if (output != '\0' && f->prec >= 1)
		write(1, &output, 1);
	else
		return ;
}

char	*char_width(char output, t_all *f)
{
	char	*new;
	int		i;
	int		len;

	if (f->wid_flag == 0)
		return (NULL);
	i = ft_strlen(&output);
	len = f->width > i ? f->width - i : 0;
	new = ft_strnew(len);
	ft_memset(new, ' ', len);
	f->adr += len;
	return (new);
}

char	*str_prec(char *output, t_all *f)
{
	int		i;
	int		len;
	char	*n;
	char	*x;

	x = "(null)";
	i = output != NULL ? ft_strlen(output) : ft_strlen(x);
	len = i <= f->prec ? i : f->prec;
	n = ft_strnew(len);
	f->adr += len;
	n = output != NULL ? ft_strncpy(n, output, len) : ft_strncpy(n, x, len);
	return (n);
}

char	*str_width(char *output, t_all *f)
{
	char	*new;
	int		i;
	int		g;
	int		len;

	if (f->wid_flag == 0)
		return (NULL);
	g = output != NULL ? ft_strlen(output) : 6;
	i = g > f->prec ? g : f->prec;
	len = f->width > i ? f->width - i : 0;
	new = ft_strnew(len);
	if (f->dash == 0 && f->prec_flag == 0 && f->zero == 1)
		ft_memset(new, '0', len);
	else
		ft_memset(new, ' ', len);
	f->adr += len;
	return (new);
}
