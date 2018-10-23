/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqroot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 02:21:59 by jmeier            #+#    #+#             */
/*   Updated: 2018/04/05 02:22:13 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double	ft_sqroot(double square)
{
	double	root;
	int		i;

	root = square / 3;
	i = -1;
	if (square <= 0)
		return (0);
	while (++i < 32)
		root = (root + square / root) / 2;
	return (root);
}
