/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 00:16:36 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/29 00:43:04 by jmeier           ###   ########.fr       */
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

unsigned char	*create_block(char *str, int i, int len)
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

unsigned char	*process_blk(unsigned char *blk, t_des *des, unsigned int d)
{
	unsigned char	*left;
	unsigned char	*right;
	int				i;

	left = (unsigned char *)ft_strnew(4);
	right = (unsigned char *)ft_strnew(4);
	ft_memcpy(left, blk, 4);
	ft_memcpy(right, &blk[4], 4);
	i = 0;
	while (i < 16)
	{
		if (d)
	}
}

char		*des_algo(char *in, t_ssl *ssl, t_des *des)
{
	unsigned char	*blk;
	char			*ret;
	size_t			i;

	i = 0;
	(void)in;
	ret = ft_strnew(0);
	while (i < ssl->in_size)
	{
		blk = create_block(&in[i]);
		blk = process_blk(blk, des);
		ft_memcpy(&ret[i], blk, 8);
		i += 8;
		free(blk);
	}
	ssl->ou_size = i;
	ft_memcpy(&ret[ou_size], "\0", 1);
	return (ret);
}
