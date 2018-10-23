/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 23:22:42 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/24 23:31:07 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(const char *src, int len)
{
	char	*ret;
	int		i;

	i = -1;
	NULL_GUARD(ret = ft_strnew(len));
	while (++i < len)
	{
		if (src[i] == '\0')
		{
			free(ret);
			ret = ft_strdup(src);
			return (ret);
		}
		ret[i] = src[i];
	}
	return (ret);
}
