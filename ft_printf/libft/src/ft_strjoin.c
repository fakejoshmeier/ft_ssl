/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:10:46 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 23:13:29 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		a;
	int		z;

	if (!s1 || !s2)
		return (NULL);
	len1 = (int)ft_strlen(s1);
	len2 = (int)ft_strlen(s2);
	str = ft_strnew(len1 + len2);
	if (!str)
		return (NULL);
	a = -1;
	z = -1;
	while (++a < len1)
		*(str + a) = *(s1 + a);
	while (++z < len2)
		*(str + a++) = *(s2 + z);
	return (str);
}
