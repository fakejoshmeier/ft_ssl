/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:00:24 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 22:29:27 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	int		count;
	char	*mid;

	count = -1;
	mid = dest;
	while (++count < (int)n)
	{
		*(mid + count) = *((unsigned char *)src + count);
		if (*((unsigned char *)src + count) == (unsigned char)c)
			return (dest + count + 1);
	}
	return (NULL);
}
