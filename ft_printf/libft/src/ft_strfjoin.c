/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:19:55 by jmeier            #+#    #+#             */
/*   Updated: 2018/10/22 16:19:59 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strfjoin(char *s1, char const *s2)
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
	free(s1);
	return (str);
}
