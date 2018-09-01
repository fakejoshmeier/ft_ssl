/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 00:16:36 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/31 14:41:35 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char		*des_pad(char **in, size_t *len)
{
	size_t		new;
	char		byte;
	char		*pad;

	new = ((*len / 8) + 1) * 8;
	byte = new - *len;
	pad = ft_strnew(new);
	ft_memcpy(pad, *in, *len);
	free(*in);
	*in = pad;
	while (*len < new)
		(*in)[(*len)++] = byte;
	return (*in);
}

uint64_t	process_msg(t_des *des, uint64_t msg)
{
	uint64_t	left;
	uint64_t	rite;
	uint64_t	ret;
	int			i;

	des->init_perm_ret = permute_key_by_x_for_y(msg, des->init_perm, 64);
	left = des->init_perm_ret >> 32;
	rite = des->init_perm_ret & 0xffffffff;
	des->l[0] = rite;
	des->r[0] = left ^ des_f(des, rite, des->subkey[0]);
	i = 0;
	while (++i < 16)
	{
		des->l[i] = des->r[i - 1];
		des->r[i] = des->l[i - 1] ^ des_f(des, des->r[i - 1], des->subkey[i]);
	}
	ret = ((uint64_t)des->r[15] << 32) | (uint64_t)des->l[15];
	return (permute_key_by_x_for_y(ret, des->fp, 64));
}

/*
** Expand what was once a 32 bit number to a 48 bit number with the ebit
** selection table.  Now every six bits, I play around with the bits to get a
** row and column in one of eight s-boxes.  Each box has a four bit number at
** each index, which replaces the six bit number, shrinking the output from 48
** to 32 bits.
*/

uint32_t	des_f(t_des *des, uint32_t blk, uint64_t key)
{
	uint64_t	xor;
	uint32_t	ret;
	int			row;
	int			col;
	int			i;

	i = -1;
	xor = 0;
	while (++i < 48)
		xor |= (((uint64_t)blk >> (32 - des->ebit[i])) & 1) << (48 - (i + 1));
	xor ^= key;
	blk = 0;
	i = -1;
	while (++i < 8)
	{
		row = (xor >> (42 - (6 * i))) & 0x3f;
		col = (row >> 1) & 0xf;
		row = ((row >> 4) & 2) | (row & 1);
		blk |= (uint32_t)des->s[i][row][col] << (28 - (4 * i));
	}
	i = -1;
	ret = 0;
	while (++i < 32)
		ret |= ((blk >> (32 - des->p[i])) & 1) << (32 - (i + 1));
	return (ret);
}

// So the problem seems to be that someone is copying over the memory space
char		*des_algo(char *in, t_ssl *ssl, t_des *des)
{
	uint64_t	msg;
	uint64_t	e_msg;
	char		*tmp;
	char		*ret;
	size_t		i;

	i = 0;
	ret = ft_strnew(0);
	while (i < ssl->in_size)
	{
		msg = des_str_to_64bit(&in);
		e_msg = process_msg(des, msg);
		tmp = ft_strnew(i + 8);
		ft_memcpy(tmp, ret, i);
		ft_memcpy(&tmp[i], &e_msg, 8);
		free(ret);
		ret = tmp;
		i += 8;
	}
	ssl->ou_size = i;
	return (ret);
}
