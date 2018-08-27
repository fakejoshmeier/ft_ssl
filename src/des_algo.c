/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 00:16:36 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/27 16:47:07 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char		*des_pad(char **in, size_t *len)
{
	size_t		stuffing;
	size_t		i;
	char		*pad;
	char		*tmp;

	stuffing = 8 - (*len % 8);
	pad = ft_strnew(stuffing);
	i = -1;
	while (++i < stuffing)
		pad[i] = stuffing;
	tmp = *in;
	*in = ft_strfjoin(tmp, pad);
	free(pad);
	*len += stuffing;
	return (*in);
}

unsigned char	*set_block(char *str, int i, int len)
{
	unsigned char	*ret;
	int				j;

	ret = (unsigned char *)ft_strnew(8);
	if (len - i >= 8)
		ft_memcpy(ret, &str[i], 8);
	else
	{
		ft_memcpy(ret, &str[i], len - i);
		j = 8;
		while (--j >= (len - i))
			ret[j] = 8 - (len - i);
	}
	return (ret);
}

char		*des_algo(char *in, t_ssl *ssl, t_des *des)
{
	unsigned char	blk;
	char			*ret;
	size_t			i;

	i = 0;
	(void)des;
	(void)in;
	ret = ft_strnew(0);
	while (i < ssl->in_size)
	{
		blk = set_block(in + i);
		blk = process_blk(blk, des);
		insert_blk(in + i, blk);
		i += 8;
	}
	ssl->ou_size = i;
	return (ret);
}
