/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 00:02:20 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/21 00:35:52 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*sha256_exe(t_ssl *ssl, char *input)
{
	t_sha	sha;
	
	sha256_init(&sha);
	sha256_bits(&sha, ssl, input);
}

void	sha256_bits(t_sha *sha, t_ssl *ssl, char *input)
{
	uint64_t	bits;
	uint64_t	zero_bits;

	bits = ssl->in_size * 8;
	zero_bits = 0;
	while ((bits + zero_bits + 65) % 512)
		++zero_bits;
	sha->msg = ft_memalloc(len + 1 + (zero_bits / 8) + 8);
	sha->msg = ft_memcpy(sha->msg, input, ssl->in_size);
	//endian switch
}

void	