/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:43:34 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 23:16:19 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		len;
	int		i;

	len = (int)ft_strlen(s1);
	i = -1;
	while (s2[++i] && i < (int)n)
		s1[len++] = s2[i];
	s1[len] = '\0';
	return (s1);
}
