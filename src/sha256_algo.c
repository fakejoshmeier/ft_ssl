/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:47:36 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/27 22:40:04 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	sha256_words(t_sha *sha, size_t *j)
{
	int			i;
	uint32_t	s0;
	uint32_t	s1;

	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			sha->w[i] = ((uint32_t)sha->msg[(*j)++] << 24) |
			(((uint32_t)sha->msg[(*j)++]) << 16) |
			(((uint32_t)sha->msg[(*j)++]) << 8) |
			((uint32_t)sha->msg[(*j)++]);
		else if (16 <= i)
		{
			s0 = RITE_ROT(sha->w[i - 15], 7) ^ RITE_ROT(sha->w[i - 15], 18) ^
				sha->w[i - 15] >> 3;
			s1 = RITE_ROT(sha->w[i - 2], 17) ^ RITE_ROT(sha->w[i - 2], 19) ^
				sha->w[i - 2] >> 10;
			sha->w[i] = sha->w[i - 16] + s0 + sha->w[i - 7] + s1;
		}
	}
}

void	sha256_var_init(t_sha *sha)
{
	sha->a = sha->h0;
	sha->b = sha->h1;
	sha->c = sha->h2;
	sha->d = sha->h3;
	sha->e = sha->h4;
	sha->f = sha->h5;
	sha->g = sha->h6;
	sha->h = sha->h7;
}

void	sha256_algo(t_sha *sha)
{
	uint32_t	s0;
	uint32_t	s1;
	uint32_t	ch;
	uint32_t	maj;
	int			i;

	i = -1;
	while (++i < 64)
	{
		s1 = RITE_ROT(sha->e, 6) ^ RITE_ROT(sha->e, 11) ^ RITE_ROT(sha->e, 25);
		ch = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
		sha->t1 = sha->h + s1 + ch + sha->k[i] + sha->w[i];
		s0 = RITE_ROT(sha->a, 2) ^ RITE_ROT(sha->a, 13) ^ RITE_ROT(sha->a, 22);
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

void	sha256_add_chunk(t_sha *sha)
{
	sha->h0 += sha->a;
	sha->h1 += sha->b;
	sha->h2 += sha->c;
	sha->h3 += sha->d;
	sha->h4 += sha->e;
	sha->h5 += sha->f;
	sha->h6 += sha->g;
	sha->h7 += sha->h;
}
