/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:01:45 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 22:29:39 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				count;
	unsigned char	*str;
	unsigned char	i;

	count = -1;
	i = (unsigned char)c;
	str = (unsigned char *)s;
	while (++count < (int)n)
	{
		if (str[count] == i)
			return ((void *)str + count);
	}
	return (NULL);
}
