/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:46:00 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 23:19:04 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
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
