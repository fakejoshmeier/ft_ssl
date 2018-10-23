/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josh <jmeier@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 22:56:40 by josh              #+#    #+#             */
/*   Updated: 2018/08/16 23:15:06 by josh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**ret;

	if (!arr)
		return (NULL);
	i = -1;
	while (arr[++i] != NULL)
		;
	NULL_GUARD(ret = (char **)ft_memalloc(sizeof(char *) * i));
	ret[i] = NULL;
	while (--i > -1)
	{
		if (!(ret[i] = ft_strdup(arr[i])))
		{
			ft_freearr(ret);
			return (NULL);
		}
	}
	return (ret);
}
