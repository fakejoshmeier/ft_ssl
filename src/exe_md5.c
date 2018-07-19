/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_md5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:21:58 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/18 23:40:02 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*exe_md5(t_ssl *ssl, char *input)
{
	t_md5	md5;
	size_t	i;
	int		j;

	init_md5(&md5, -1);
	append_bits(&md5, ssl, input);
	i = -1;
	while (++i < ((ssl->in_size * 8) / 512))
	{
		ft_memcpy(md5.m, &md5.msg[i * 64], 64);
		md5.a2 = md5.a;
		md5.b2 = md5.b;
		md5.c2 = md5.c;
		md5.d2 = md5.d;
		j = -1;
		while (++j < 64)
			md5_algo(&md5, j);
		md5.a += md5.a2;
		md5.b += md5.b2;
		md5.c += md5.c2;
		md5.d += md5.d2;
	}
	ft_free(md5.msg);
	return (md5_out(&md5));
}

/*
** Count number of needed bits, allocate a block of that size, copy input
** onto that block, append original length in bits as 64 bit number to the
** end.  Or since it's memcpy, stuff it in.
*/

void	append_bits(t_md5 *md5, t_ssl *ssl, char *input)
{
	size_t		bits;
	uint64_t	og_bit_length;

	og_bit_length = ssl->in_size * 8;
	bits = og_bit_length + 1;
	while (bits % 512 != 448)
		++bits;
	bits /= 8;
	md5->msg = ft_memalloc(bits + 64);
	ft_memcpy(md5->msg, input, ssl->in_size);
	md5->msg[ssl->in_size] = 0b10000000;
	ft_memcpy(md5->msg + bits, &og_bit_length, 8);
	ssl->in_size = bits + 8;
	ssl->ou_size = 32;
}

/*
** en.wikipedia.org/wiki/MD5#Algorithm
*/

void	md5_algo(t_md5 *md5, int i)
{
	if (i < 16)
	{
		md5->f = MD5_F1(md5->b2, md5->c2, md5->d2);
		md5->g = i;
	}
	else if (16 <= i && i < 32)
	{
		md5->f = MD5_F2(md5->b2, md5->c2, md5->d2);
		md5->g = (5 * i + 1) % 16;
	}
	else if (32 <= i && i < 48)
	{
		md5->f = MD5_F3(md5->b2, md5->c2, md5->d2);
		md5->g = (3 * i + 5) % 16;
	}
	else if (48 <= i && i < 64)
	{
		md5->f = MD5_F4(md5->b2, md5->c2, md5->d2);
		md5->g = (7 * i) % 16;
	}
	md5->f = md5->f + md5->a2 + md5->k[i] + md5->m[md5->g];
	md5->a2 = md5->d2;
	md5->d2 = md5->c2;
	md5->c2 = md5->b2;
	md5->b2 = md5->b2 + LEFT_ROT(md5->f, md5->s[i]);
}

//figure out how to append 

char	*md5_out(t_md5 *md5)
{
	t_u32		u;
	char		*ret;
	char		*str;
	int			i;
	int			j;

	NULL_GUARD(ret = (char *)ft_memalloc(33));
	str = "0123456789abcdef";
	i = 0;
	j = 0;
	while (i < 32)
	{
		MATCH(i < 8, u.init = md5->a);
		OR(8 <= i && i < 16, u.init = md5->b);
		OR(16 <= i && i < 32, u.init = i < 24 ? md5->c : md5->d);
		ret[i++] = str[u.nugget[j % 4] >> 4];
		ret[i++] = str[u.nugget[j % 4] & 15];
		++j;
	}
	ret[32] = '\0';
	return (ret);
}