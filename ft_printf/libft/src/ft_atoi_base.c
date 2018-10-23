/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 23:26:57 by jmeier            #+#    #+#             */
/*   Updated: 2018/02/11 00:22:04 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	convert_and_check_nb(char c, int base)
{
	int		ret;

	ret = -1;
	if (c >= '0' && c <= '9')
		ret = c - '0';
	else if (c >= 'a' && c <= 'z')
		ret = c - 97 + 10;
	else if (c >= 'A' && c <= 'Z')
		ret = c - 65 + 10;
	if (ret < base && ret)
		return (ret);
	return (-1);
}

static int	len(char *str, int base)
{
	int		len;

	len = -1;
	while (str[++len])
		if (convert_and_check_nb(str[len], base) == -1)
			break ;
	return (len);
}

int			ft_atoi_base(char *nb, int base)
{
	int		ret;
	int		l;

	if (base == 10)
		return (ft_atoi(nb));
	while (ft_isspace(*nb))
		++nb;
	if (nb[0] == '0' && (nb[1] == 'x' || nb[1] == 'X') && base == 16)
		nb += 2;
	ret = 0;
	l = len(nb, base) - 1;
	while (*nb && l >= 0 && convert_and_check_nb(*nb, base) != -1)
	{
		ret += convert_and_check_nb(*nb, base) * ft_pow(base, l);
		++nb;
		--l;
	}
	return (ret);
}
