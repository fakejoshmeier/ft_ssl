/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:15:15 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 22:31:31 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t byte)
{
	char	*temp_d;
	char	*temp_s;
	int		i;

	i = -1;
	temp_d = (char *)dst;
	temp_s = (char *)src;
	if (temp_s < temp_d)
		while ((int)(--byte) >= 0)
			temp_d[byte] = temp_s[byte];
	else
		while (++i < (int)byte)
			temp_d[i] = temp_s[i];
	return (dst);
}
