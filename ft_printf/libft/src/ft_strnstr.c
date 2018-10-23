/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:27:32 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/27 17:51:02 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lil, size_t len)
{
	int		marker;
	int		i;
	int		j;
	int		k;

	if (!ft_strlen(lil))
		return ((char *)big);
	i = -1;
	marker = 0;
	while (*(big + ++i) && !marker && i < (int)len)
	{
		if (*(big + i) == *(lil + 0))
		{
			j = 0;
			k = i;
			marker = 1;
			while (*(lil + j) && *(big + k) && k < (int)len && j < (int)len)
				if (*(lil + j++) != *(big + k++))
					marker = 0;
			if (marker && !*(lil + j))
				return ((char *)big + i);
		}
	}
	return (NULL);
}
