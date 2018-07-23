/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 00:02:20 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/22 18:23:45 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*sha256_exe(t_ssl *ssl, char *input)
{
	t_sha	sha;
	size_t	chunks;
	size_t	i;
	size_t	j;

	sha256_init(&sha);
	sha256_bits(&sha, ssl, input);
	chunks = (ssl->in_size * 8) / 512;
	i = -1;
	j = 0;
	while (++i < chunks)
	{
		sha256_words(&sha);
		sha256_var_init(&sha);
		sha256_algo(&sha);
		sha256_add_chunk(&sha);
	}
	return (sha256_out(&sha));
}

void	sha256_bits(t_sha *sha, t_ssl *ssl, char *input)
{
	uint64_t	bits;
	uint64_t	zero_bits;

	bits = ssl->in_size * 8;
	zero_bits = 0;
	while ((bits + zero_bits + 65) % 512)
		++zero_bits;
	sha->msg = ft_memalloc(ssl->in_size + 1 + (zero_bits / 8) + 8);
	ft_memcpy(sha->msg, input, ssl->in_size);
	sha->msg[ssl->in_size] = 128;
	bits = b_endian64(bits);
	ft_memcpy(sha->msg + ssl->in_size + 1 + (zero_bits / 8), &bits, 8);
	ssl->in_size = ssl->in_size + 1 + (zero_bits / 8) + 8;
}

char	*sha256_out(t_sha *sha)
{
	t_u32	u;
	char	*ret;
	char	*str;
	int		i;
	int		j;

	NULL_GUARD(ret = (char *)ft_memalloc(33));
	str = "0123456789abcdef";
	i = 0;
	j = 0;
	while (i < 32)
	{
		MATCH(i < )
	}
	ret[32] = '\0';
	return (ret);
}