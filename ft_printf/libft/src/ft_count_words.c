/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:19:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/03/27 23:19:54 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_count_words(char *str, char c)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] != c && i == 0)
			++count;
		else if (str[i] != c && str[i - 1] == c)
			++count;
	}
	return (count);
}
