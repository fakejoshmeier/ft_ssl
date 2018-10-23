/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:24:42 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 22:56:37 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	int		i;

	dst_len = ft_strlen(dst);
	i = -1;
	while (src[++i])
		dst[(int)dst_len + i] = src[i];
	dst[(int)dst_len + i] = '\0';
	return (dst);
}
