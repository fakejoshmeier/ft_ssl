/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 12:20:44 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/19 16:39:06 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char		*cbc_exe(t_ssl *ssl, char *in)
{
	t_des		des;
	char		*ret;
	char		*tmp;

	des_init(&des);
	des_pbkdf(ssl, &des, &in);
	des_subkeys(&des, ssl->flag->d, des.key);
	des.iv = b_endian64(hex_str_to_64bit(ssl->user_iv));
	if (ssl->flag->a && ssl->flag->d)
	{
		tmp = base64_exe(ssl, in);
		in = tmp;
		ssl->in_size = ssl->ou_size;
	}
	ret = ssl->flag->d ? cbc_decrypt(&des, ssl, in) :
		cbc_encrypt(&des, ssl, in);
	if (ssl->flag->a && !ssl->flag->d)
	{
		ssl->in_size = ssl->ou_size;
		tmp = base64_exe(ssl, ret);
		ret = tmp;
	}
	MATCH(!ssl->flag->a, free(in));
	des_clean(ssl, &des);
	return (ret);
}

char		*cbc_encrypt(t_des *des, t_ssl *ssl, char *in)
{
	uint64_t	msg;
	uint64_t	e_msg;
	char		*ret;
	size_t		i;
	size_t		j;

	i = ssl->in_size;
	ssl->in_size += (ssl->in_size % 8) == 0 ? 8 : 0;
	ret = des_enc_out(ssl, des);
	while (ssl->ou_size < ssl->in_size)
	{
		msg = des_str_to_64bit(&in, &i) ^ des->iv;
		e_msg = process_msg(des, msg);
		des->iv = e_msg;
		j = -1;
		while (++j < 8)
			ret[ssl->ou_size + j] = (e_msg >> (56 - (j * 8))) & 0xff;
		ssl->ou_size += 8;
	}
	ret -= ssl->user_pass ? 16 : 0;
	ssl->ou_size += ssl->user_pass ? 16 : 0;
	return (ret);
}

char		*cbc_decrypt(t_des *des, t_ssl *ssl, char *in)
{
	uint64_t	msg;
	uint64_t	d_msg;
	size_t		i;
	size_t		j;
	char		*ret;

	MATCH(ssl->in_size % 8 != 0,
		ft_error("Bad decrypt: Incorrect input size.", 1));
	ret = ft_strnew(ssl->in_size);
	i = ssl->in_size;
	while (ssl->ou_size < ssl->in_size)
	{
		msg = des_str_to_64bit_dec(&in, &i);
		d_msg = process_msg(des, msg) ^ des->iv;
		des->iv = d_msg;
		j = -1;
		while (++j < 8)
			ret[ssl->ou_size + j] = (d_msg >> (56 - (j * 8))) & 0xff;
		ssl->ou_size += 8;
	}
	return (ret);
}
