/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 03:13:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/28 21:19:58 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*sha512_exe(t_ssl *ssl, char *in)
{
	t_s512	sha;
	size_t	chunks;
	size_t	i;

	sha512_init(&sha);
	sha512_bits(&sha, ssl, in);
	chunks = ssl->in_size / 128;
	i = -1;
	while (++i < chunks)
	{
		sha512_words(&sha, (sha.msg + (i * 128)));
		sha512_round(&sha);
	}
	ft_free(sha.msg);
	return (sha512_out(&sha));
}

/*
** SHA-512 requires a 128 bit integer appended at the end.  Since I can't
** find such a thing and have no intention of making one
** (an unsigned long long long?), I am hedging my bets on never having to hash
** a message over 2.306e18 characters long.
*/

void	sha512_bits(t_s512 *sha, t_ssl *ssl, char *input)
{
	uint64_t	bits;
	uint64_t	zero_bits;

	bits = ssl->in_size * 8;
	zero_bits = 0;
	while ((bits + zero_bits + 65) % 1024)
		++zero_bits;
	sha->msg = ft_memalloc(ssl->in_size + 1 + (zero_bits / 8) + 8);
	ft_memcpy(sha->msg, input, ssl->in_size);
	sha->msg[ssl->in_size] = 128;
	bits = b_endian64(bits);
	ft_memcpy(sha->msg + ssl->in_size + 1 + (zero_bits / 8), &bits, 8);
	ssl->in_size = ssl->in_size + 1 + (zero_bits / 8) + 8;
	ssl->ou_size = 128;
}

char	*sha512_out(t_s512 *sha)
{
	t_u64			u;
	char			*ret;
	char			*str;
	int				i;
	unsigned int	j;

	NULL_GUARD(ret = (char *)ft_memalloc(129));
	str = "0123456789abcdef";
	i = 0;
	j = 7;
	while (i < 128)
	{
		MATCH(i < 32, u.init = i < 16 ? sha->h0 : sha->h1);
		OR(32 <= i && i < 64, u.init = i < 48 ? sha->h2 : sha->h3);
		OR(64 <= i && i < 96, u.init = i < 80 ? sha->h4 : sha->h5);
		OR(96 <= i && i < 128, u.init = i < 112 ? sha->h6 : sha->h7);
		ret[i++] = str[(u.nugget[j % 8] >> 4) & 0xf];
		ret[i++] = str[u.nugget[j-- % 8] & 0xf];
	}
	ret[128] = '\0';
	return (ret);
}
