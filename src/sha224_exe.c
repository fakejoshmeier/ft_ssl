/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 01:07:38 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/10 15:11:02 by josh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

/*
** The algorithm for SHA224 is the same as SHA256, so why not?.
** Main differences are that the initial H values are different and H7 is not
** used in the final digest
*/

char	*sha224_exe(t_ssl *ssl, char *input)
{
	t_sha	sha;
	size_t	chunks;
	size_t	i;

	sha224_init(&sha);
	sha256_bits(&sha, ssl, input);
	chunks = ssl->in_size / 64;
	i = -1;
	while (++i < chunks)
	{
		sha256_words(&sha, (sha.msg + (i * 64)));
		sha256_round(&sha);
	}
	ft_free(sha.msg);
	ssl->ou_size = 28;
	return (sha224_out(&sha));
}

void	sha224_init(t_sha *sha)
{
	sha->h0 = 0xc1059ed8;
	sha->h1 = 0x367cd507;
	sha->h2 = 0x3070dd17;
	sha->h3 = 0xf70e5939;
	sha->h4 = 0xffc00b31;
	sha->h5 = 0x68581511;
	sha->h6 = 0x64f98fa7;
	sha->h7 = 0xbefa4fa4;
	sha->k[0] = 0x428a2f98;
	sha->k[1] = 0x71374491;
	sha->k[2] = 0xb5c0fbcf;
	sha->k[3] = 0xe9b5dba5;
	sha->k[4] = 0x3956c25b;
	sha->k[5] = 0x59f111f1;
	sha->k[6] = 0x923f82a4;
	sha->k[7] = 0xab1c5ed5;
	sha->k[8] = 0xd807aa98;
	sha->k[9] = 0x12835b01;
	sha->k[10] = 0x243185be;
	sha->k[11] = 0x550c7dc3;
	sha->k[12] = 0x72be5d74;
	sha->k[13] = 0x80deb1fe;
	sha->k[14] = 0x9bdc06a7;
	sha->k[15] = 0xc19bf174;
	sha256_init1(sha);
}

char	*sha224_out(t_sha *sha)
{
	t_u32			u;
	char			*ret;
	char			*str;
	int				i;
	unsigned int	j;

	NULL_GUARD(ret = (char *)ft_memalloc(57));
	str = "0123456789abcdef";
	j = 3;
	i = 0;
	while (i < 56)
	{
		MATCH(i < 16, u.init = i < 8 ? sha->h0 : sha->h1);
		OR(16 <= i && i < 32, u.init = i < 24 ? sha->h2 : sha->h3);
		OR(32 <= i && i < 48, u.init = i < 40 ? sha->h4 : sha->h5);
		OR(48 <= i, u.init = sha->h6);
		ret[i++] = str[(u.nugget[j % 4] >> 4) & 0xf];
		ret[i++] = str[u.nugget[j-- % 4] & 0xf];
	}
	ret[56] = '\0';
	return (ret);
}
