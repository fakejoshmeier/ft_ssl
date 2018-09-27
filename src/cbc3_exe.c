/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc3_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 02:30:51 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/27 02:45:10 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*cbc3_exe(t_ssl *ssl, char *in)
{
	t_des		des;
	char		*ret;

	des_init(&des);
	des_pbkdf(ssl, &des, &in);
	distribute_key(ssl, &des);
	des_subkeys(&des, ssl->flag->d, des.key, des.subkey);
	des_subkeys(&des, !ssl->flag->d, des.key2, des.subkey2);
	des_subkeys(&des, ssl->flag->d, des.key3, des.subkey3);
	des.iv = b_endian64(hex_str_to_64bit(ssl->user_iv));
	ret = ssl->flag->d ? cbc3_decrypt(&des, ssl, in) :
		cbc3_encrypt(&des, ssl, in);
	free(in);
	des_clean(ssl, &des);
	return (ret);
}

char	*cbc3_encrypt(t_des *des, t_ssl *ssl, char *in)
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
		e_msg = process_msg(des, msg, des->subkey);
		msg = process_msg(des, e_msg, des->subkey2);
		e_msg = process_msg(des, msg, des->subkey3);
		des->iv = e_msg;
		j = -1;
		while (++j < 8)
			ret[ssl->ou_size + j] = (e_msg >> (56 -(j * 8))) & 0xff;
		ssl->ou_size += 8;
	}
	ret -= ssl->user_pass ? 16 : 0;
	ssl->ou_size += ssl->user_pass ? 16 : 0;
	return (ret);
}

char	*cbc3_decrypt(t_des *des, t_ssl *ssl, char *in)
{
	uint64_t	msg;
	uint64_t	d_msg;
	char		*ret;
	size_t		i;
	size_t		j;

	MATCH(ssl->in_size % 8 != 0,
		ft_error("Bad decrypt: Incorrect input size.", 1));
	ret = ft_strnew(ssl->in_size);
	i = ssl->in_size;
	while (ssl->ou_size < ssl->in_size)
	{
		msg = des_str_to_64bit_dec(&in, &i);
		d_msg = process_msg(des, msg, des->subkey3);
		d_msg = process_msg(des, d_msg, des->subkey2);
		d_msg = process_msg(des, d_msg, des->subkey) ^ des->iv;
		des->iv = msg;
		j = -1;
		while (++j < 8)
			ret[ssl->ou_size + j] = (d_msg >> (56 -(j * 8))) & 0xff;
		ssl->ou_size += 8;
	}
	return (ret);
}
