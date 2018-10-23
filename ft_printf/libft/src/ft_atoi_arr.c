/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 22:52:13 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/25 21:22:32 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		*ft_atoi_arr(char *str)
{
	char	**tmp;
	int		*ret;
	int		i;
	int		j;

	tmp = ft_strsplit(str, ' ');
	i = 0;
	while (tmp[i])
		i++;
	NULL_GUARD(ret = (int *)ft_memalloc(sizeof(int) * i));
	j = -1;
	while (++j < i)
	{
		ret[j] = ft_atoi(tmp[j]);
		free(tmp[j]);
	}
	free(tmp);
	return (ret);
}
