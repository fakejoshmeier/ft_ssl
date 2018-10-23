/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:35:33 by jmeier            #+#    #+#             */
/*   Updated: 2018/10/22 16:19:26 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base(int value, int base)
{
	int		len;
	long	nbr;
	char	*pointer;
	char	*base_string;

	base_string = "0123456789abcdef";
	if (value == 0)
		return ("0");
	len = 0;
	nbr = value;
	len = ft_numlen(nbr, base);
	if (nbr < 0 && base == 10)
		len += 1;
	if (nbr < 0)
		nbr *= -1;
	NULL_GUARD(pointer = ft_strnew(len));
	while (nbr)
	{
		pointer[--len] = base_string[nbr % base];
		nbr /= base;
	}
	if (value < 0 && base == 10)
		pointer[0] = '-';
	return (pointer);
}
