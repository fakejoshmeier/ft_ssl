/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 04:39:34 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/28 21:11:06 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	sha512_words(t_s512 *sha, uint8_t *msg)
{
	int			i;
	uint64_t	s0;
	uint64_t	s1;
	uint64_t	*chunk;

	i = -1;
	chunk = (uint64_t *)msg;
	while (++i < 80)
	{
		if (i < 16)
			sha->w[i] = b_endian64(chunk[i]);
		else
		{
			s0 = S512_ROT(sha->w[i - 15], 1) ^ S512_ROT(sha->w[i - 15], 8) ^
				(sha->w[i - 15] >> 7);
			s1 = S512_ROT(sha->w[i - 2], 19) ^ S512_ROT(sha->w[i - 2], 61) ^
				(sha->w[i - 2] >> 6);
			sha->w[i] = sha->w[i - 16] + s0 + sha->w[i - 7] + s1;
		}
	}
}

void	sha512_round(t_s512 *sha)
{
	sha->a = sha->h0;
	sha->b = sha->h1;
	sha->c = sha->h2;
	sha->d = sha->h3;
	sha->e = sha->h4;
	sha->f = sha->h5;
	sha->g = sha->h6;
	sha->h = sha->h7;
	sha512_algo(sha);
	sha->h0 += sha->a;
	sha->h1 += sha->b;
	sha->h2 += sha->c;
	sha->h3 += sha->d;
	sha->h4 += sha->e;
	sha->h5 += sha->f;
	sha->h6 += sha->g;
	sha->h7 += sha->h;
}

void	sha512_algo(t_s512 *sha)
{
	uint64_t	s0;
	uint64_t	s1;
	uint64_t	ch;
	uint64_t	maj;
	int			i;

	i = -1;
	while (++i < 80)
	{
		s1 = S512_ROT(sha->e, 14) ^ S512_ROT(sha->e, 18) ^ S512_ROT(sha->e, 41);
		ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
		sha->t1 = sha->h + s1 + ch + sha->k[i] + sha->w[i];
		s0 = S512_ROT(sha->a, 28) ^ S512_ROT(sha->a, 34) ^ S512_ROT(sha->a, 39);
		maj = (sha->a & sha->b) ^ (sha->a & sha->c) ^ (sha->b & sha->c);
		sha->t2 = s0 + maj;
		sha->h = sha->g;
		sha->g = sha->f;
		sha->f = sha->e;
		sha->e = sha->d + sha->t1;
		sha->d = sha->c;
		sha->c = sha->b;
		sha->b = sha->a;
		sha->a = sha->t1 + sha->t2;
	}
}
