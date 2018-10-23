/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:02:47 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 22:25:42 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = -1;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (++i < (int)n && str1[i] == str2[i])
		;
	if (i == (int)n)
		return (0);
	return (*(str1 + i) - *(str2 + i));
}
