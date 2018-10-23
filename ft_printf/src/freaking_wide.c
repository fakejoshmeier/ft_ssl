/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freaking_wide.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 02:01:55 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 21:31:31 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_widelen(wchar_t *s)
{
	int		i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

wchar_t	*ft_wstrnew(int n)
{
	wchar_t	*str;

	str = (wchar_t *)malloc(sizeof(wchar_t) * n + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, n + 1);
	return (str);
}

wchar_t	*ft_wstrncpy(wchar_t *dst, wchar_t *src, size_t n)
{
	int		i;

	i = -1;
	while (++i < (int)n)
	{
		if (src[i])
			dst[i] = src[i];
		else
		{
			while (i < (int)n)
				dst[i++] = '\0';
		}
	}
	return (dst);
}

wchar_t	*wchar_prec(wchar_t *output, t_all *f)
{
	int		i;
	int		len;
	wchar_t	*n;
	char	*x;
	char	*y;

	if (f->prec_flag == 0)
		return (NULL);
	x = "(null)";
	i = output != NULL ? ft_widelen(output) : 6;
	len = i <= f->prec ? i : f->prec;
	n = ft_wstrnew(len);
	f->adr += len;
	n = output != NULL ? ft_wstrncpy(n, output, len) : '\0';
	if (n == '\0')
	{
		y = ft_strnew(len);
		y = ft_strncpy(y, x, len);
		ft_putstr(y);
		free(y);
		y = NULL;
	}
	return (n);
}

char	*wchar_width(wchar_t *out, t_all *f)
{
	char	*new;
	int		i;
	int		len;

	if (f->wid_flag == 0)
		return (NULL);
	i = ft_widelen(out);
	len = f->width > i ? f->width - i : 0;
	new = ft_strnew(len);
	ft_memset(new, ' ', len);
	f->adr += len;
	return (new);
}
