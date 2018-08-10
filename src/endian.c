/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 16:53:36 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/10 14:41:39 by josh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

/*
** Returns 1 for little endian systems and 0 for big endian systems
*/

int			check_endianness(void)
{
	unsigned int	i;
	char			*c;

	i = 1;
	c = (char *)&i;
	if (*c)
		return (1);
	else
		return (0);
}

uint64_t	b_endian64(uint64_t num)
{
	t_u64			u;

	u.init = num;
	if (check_endianness())
		return ((((uint64_t)(u.nugget[0])) << 56) |
			(((uint64_t)(u.nugget[1])) << 48) |
			(((uint64_t)(u.nugget[2])) << 40) |
			(((uint64_t)(u.nugget[3])) << 32) |
			(((uint64_t)(u.nugget[4])) << 24) |
			(((uint64_t)(u.nugget[5])) << 16) |
			(((uint64_t)(u.nugget[6])) << 8) |
			(((uint64_t)(u.nugget[7]))));
	else
		return (num);
}

uint32_t	b_endian32(uint32_t num)
{
	t_u32			u;

	u.init = num;
	if (check_endianness())
		return ((((uint32_t)(u.nugget[0])) << 24) |
			(((uint32_t)(u.nugget[1])) << 16) |
			(((uint32_t)(u.nugget[2])) << 8) |
			(((uint32_t)(u.nugget[3]))));
	else
		return (num);
}
