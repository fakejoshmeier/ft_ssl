/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 21:42:02 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/28 21:49:46 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*sha384_exe(t_ssl *ssl, char *in)
{
	t_s512	sha;
	size_t	chunks;
	size_t	i;

	sha384_init(&sha);
	sha512_bits(&sha, ssl, in);
	chunks = ssl->in_size / 128;
	i = -1;
	while (++i < chunks)
	{
		sha512_words(&sha, (sha.msg + (i * 128)));
		sha512_round(&sha);
	}
	ft_free(sha.msg);
	return (sha384_out(&sha));
}

void	sha384_init(t_s512 *sha)
{
	sha->h0 = 0xcbbb9d5dc1059ed8;
	sha->h1 = 0x629a292a367cd507;
	sha->h2 = 0x9159015a3070dd17;
	sha->h3 = 0x152fecd8f70e5939;
	sha->h4 = 0x67332667ffc00b31;
	sha->h5 = 0x8eb44a8768581511;
	sha->h6 = 0xdb0c2e0d64f98fa7;
	sha->h7 = 0x47b5481dbefa4fa4;
	sha512_init1(sha);
	sha512_init2(sha);
	sha512_init3(sha);
	sha512_init4(sha);
}

char	*sha384_out(t_s512 *sha)
{
		t_u64			u;
	char			*ret;
	char			*str;
	int				i;
	unsigned int	j;

	NULL_GUARD(ret = (char *)ft_memalloc(97));
	str = "0123456789abcdef";
	i = 0;
	j = 7;
	while (i < 96)
	{
		MATCH(i < 32, u.init = i < 16 ? sha->h0 : sha->h1);
		OR(32 <= i && i < 64, u.init = i < 48 ? sha->h2 : sha->h3);
		OR(64 <= i && i < 96, u.init = i < 80 ? sha->h4 : sha->h5);
		ret[i++] = str[(u.nugget[j % 8] >> 4) & 0xf];
		ret[i++] = str[u.nugget[j-- % 8] & 0xf];
	}
	ret[96] = '\0';
	return (ret);
}