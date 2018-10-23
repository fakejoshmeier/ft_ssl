/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 20:15:54 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/17 21:22:24 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_b(char *s, char c)
{
	int		a;

	a = 0;
	while ((s[a]) && s[a] == c)
		a++;
	return (a);
}

static int	char_e(char *s, char c)
{
	int		a;

	a = ft_strlen(s) - 1;
	while (s[a] == c)
		a--;
	return (a);
}

char		*ft_strctrim(char const *s, char c)
{
	int		a;
	int		b;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	a = char_b((char *)s, c);
	b = char_e((char *)s, c);
	if (a == ft_strlen(s) || b == 0)
		return (ft_strnew(0));
	str = ft_strnew((b - a) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (a <= b)
		str[i++] = s[a++];
	return (str);
}
