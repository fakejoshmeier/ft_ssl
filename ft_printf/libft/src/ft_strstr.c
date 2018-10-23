/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:20:49 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/24 23:24:14 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	marker;
	int		i;
	int		j;
	int		k;

	if (!ft_strlen(little))
		return ((char *)big);
	i = -1;
	marker = 0;
	while (*(big + ++i) && !marker)
	{
		if (*(big + i) == *(little + 0))
		{
			j = 0;
			k = i;
			marker = 1;
			while (*(little + j))
				if (*(little + j++) != *(big + k++))
					marker = 0;
			if (marker)
				return ((char *)big + i);
		}
	}
	return (NULL);
}
