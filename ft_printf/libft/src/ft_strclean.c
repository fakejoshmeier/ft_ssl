/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 10:34:29 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/30 10:43:59 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_strclean(char *s)
{
	int		i;
	int		flag;

	if (!s)
		return (NULL);
	i = 0;
	flag = 0;
	while (s[i + flag])
	{
		while (s[i + flag] && ft_isspace(s[i + flag]))
			++flag;
		if ((s[i] = s[i + flag]))
			++i;
	}
	s[i] = '\0';
	return (s);
}
