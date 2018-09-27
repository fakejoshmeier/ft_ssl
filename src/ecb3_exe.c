/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb3_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 22:05:22 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/27 01:33:24 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*ecb3_exe(t_ssl *ssl, char *in)
{
	t_des		des;
	char		*ret;

	des_init(&des);
	des_pbkdf(ssl, &des, &in);
	distribute_key(ssl, &des);
	des_subkeys(&des, ssl->flag->d, des.key, des.subkey);
	des_subkeys(&des, !ssl->flag->d, des.key2, des.subkey2);
	des_subkeys(&des, ssl->flag->d, des.key3, des.subkey3);
	ret = ssl->flag->d ? ecb3_decrypt(&des, ssl, in) :
		ecb3_encrypt(&des, ssl, in);
	free(in);
	des_clean(ssl, &des);
	return (ret);
}

void	distribute_key(t_ssl *ssl, t_des *des)
{
	char		*tmp;

	if (ssl->flag->k)
	{
		tmp = ft_strndup(ssl->user_key, 16);
		des->key = blender(tmp);
		free(tmp);
		tmp = ft_strndup(&ssl->user_key[16], 16);
		des->key2 = blender(tmp);
		free(tmp);
		tmp = ft_strndup(&ssl->user_key[32], 16);
		des->key3 = blender(tmp);
	}
	else
	{
		tmp = ft_strndup(&des->hash[16], 16);
		des->key2 = blender(tmp);
		free(tmp);
		tmp = ft_strndup(&des->hash[32], 16);
		des->key3 = blender(tmp);
	}
	free(tmp);
}

char	*ecb3_encrypt(t_des *des, t_ssl *ssl, char *in)
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
		msg = des_str_to_64bit(&in, &i);
		e_msg = process_msg(des, msg, des->subkey);
		msg = process_msg(des, e_msg, des->subkey2);
		e_msg = process_msg(des, msg, des->subkey3);
		j = -1;
		while (++j < 8)
			ret[ssl->ou_size + j] = (e_msg >> (56 -(j * 8))) & 0xff;
		ssl->ou_size += 8;
	}
	ret -= ssl->user_pass ? 16 : 0;
	ssl->ou_size += ssl->user_pass ? 16 : 0;
	return (ret);
}

char	*ecb3_decrypt(t_des *des, t_ssl *ssl, char *in)
{
	uint64_t	msg;
	uint64_t	e_msg;
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
		e_msg = process_msg(des, msg, des->subkey);
		msg = process_msg(des, e_msg, des->subkey2);
		e_msg = process_msg(des, msg, des->subkey3);
		j = -1;
		while (++j < 8)
			ret[ssl->ou_size + j] = (e_msg >> (56 -(j * 8))) & 0xff;
		ssl->ou_size += 8;
	}
	return (ret);
}
