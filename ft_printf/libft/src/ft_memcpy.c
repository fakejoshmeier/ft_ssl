/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:01 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/21 20:13:46 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*d;
	char	*s;

	i = -1;
	d = dst;
	s = (char *)src;
	if (!src)
		return (dst);
	while (++i < (int)n)
		*(d + i) = *(s + i);
	return (dst);
}
