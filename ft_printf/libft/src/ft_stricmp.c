/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stricmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 14:06:35 by jmeier            #+#    #+#             */
/*   Updated: 2018/04/08 14:06:41 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stricmp(char const *a, char const *b)
{
	size_t	i;
	int		j;

	i = 0;
	j = -1;
	while (a[++j])
		ft_tolower(a[j]);
	j = -1;
	while (b[++j])
		ft_tolower(b[j]);
	while (a[i] && a[i] == b[i])
		i++;
	return ((*((unsigned char *)a + i)) - (*((unsigned char *)b + i)));
}
