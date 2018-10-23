/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 23:31:34 by jmeier            #+#    #+#             */
/*   Updated: 2017/12/12 21:35:47 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	blank_space_b(char *s)
{
	int		a;

	a = 0;
	while ((s[a]) && ft_isspace(s[a]))
		a++;
	return (a);
}

static int	blank_space_e(char *s)
{
	int		a;

	a = ft_strlen(s) - 1;
	while (ft_isspace(s[a]))
		a--;
	return (a);
}

char		*ft_strtrim(char const *s)
{
	int		a;
	int		b;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	a = blank_space_b((char *)s);
	b = blank_space_e((char *)s);
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
