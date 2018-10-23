/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 16:10:03 by jmeier            #+#    #+#             */
/*   Updated: 2017/09/25 20:11:01 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_c(char const *str, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static int	word_len(char const *str, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	size_t	j;
	size_t	k;
	char	**str;

	if (!s || !(str = (char **)malloc(sizeof(*str) * (word_c(s, c) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < word_c(s, c))
	{
		k = 0;
		if (!(str[i] = ft_strnew(word_len(&s[j], c) + 1)))
			str[i] = NULL;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			str[i][k++] = s[j++];
	}
	str[i] = 0;
	return (str);
}
