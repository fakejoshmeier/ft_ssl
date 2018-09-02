/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:54:16 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/01 17:34:44 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char		*ecb_exe(t_ssl *ssl, char *in)
{
	t_des		des;
	char		*ret;
	char		*tmp;

	des_init(&des);
	if (ssl->flag->a && ssl->flag->d)
	{
		tmp = base64_exe(ssl, in);
		in = tmp;
	}
	ret = ssl->flag->d ? ecb_decode(&des, ssl, in) : ecb_encode(&des, ssl, in);
//	MATCH(ssl->user_pass, printf("Password:%s\n", ssl->user_pass));
//	MATCH(ssl->user_salt, printf("Salt:%s\n", ssl->user_salt));
//	MATCH(ssl->user_key, printf("Key:%s\n", ssl->user_key));
//	MATCH(ssl->user_iv, printf("IV :%s\n", ssl->user_iv));
	if (ssl->flag->a && !ssl->flag->d)
	{
		tmp = base64_exe(ssl, ret);
		ret = tmp;
	}
	free(in);
	des_clean(ssl, &des);
	return (ret);
}

char		*ecb_enc_out(t_ssl *ssl, t_des *des)
{
	char		*ret;

	ret = ssl->user_pass ? ft_strnew(ssl->in_size + 24) :
		ft_strnew(ssl->in_size + 8);
	if (ssl->user_pass)
	{
		des->nacl = hex_str_to_64bit(ssl->user_salt);
		ft_memcpy(ret, "Salted__", 8);
		ft_memcpy(&ret[8], &des->nacl, 8);
		ret += 16;
	}
	ssl->in_size += ((ssl->in_size % 8) == 0) ? 8 : 0;
	return (ret);
}

char		*ecb_encode(t_des *des, t_ssl *ssl, char *in)
{
	uint64_t	msg;
	uint64_t	e_msg;
	char		*ret;
	size_t		i;
	size_t		j;

	des_pbkdf(ssl, des, 1);
	des_subkeys(des, ssl->flag->d);
	ret = ecb_enc_out(ssl, des);
	i = ssl->in_size;
	while (ssl->ou_size < ssl->in_size)
	{
		msg = des_str_to_64bit(&in, &i);
		e_msg = process_msg(des, msg);
		j = -1;
		while (++j < 8)
			ret[ssl->ou_size +j] = (e_msg >> (56 - (j * 8))) & 0xff;
		ssl->ou_size += 8;
	}
	ret -= ssl->user_pass ? 16 : 0;
	ssl->ou_size += ssl->user_pass ? 16 : 0;
///	ret[ssl->ou_size] = '\0';
	return (ret);
}

/*
 * So the thing is that des will have the salt as part of the output after the
 * input gets encrypted, so I can't *quite* create a random salt.  Actually,
 * can't I just free the salt?  All I need to do is clean up the key, iv, and
 * salt, then remake them.  I need a check for if des->nacl == whatever I
 * pull out of the input.  If it does, great.  If it doesn't, I append hash
 * repeat with nacl as a parameter, free the iv and keys, and run them through
 * blender and such.
*/

char		*ecb_decode(t_des *des, t_ssl *ssl, char *in)
{
	char	*tmp;
	char	*ret;

//	if (!ssl->flag->k)
//	{
		extract_salt(ssl, in);
		tmp = ft_strnew((ssl->in_size -= 16));
		ft_memcpy(tmp, &in[16], ssl->in_size);
		free(in);
		in = tmp;
//	}
	des->key = blender(ssl->user_key);
	des_subkeys(des, ssl->flag->d);
	ret = des_algo(in, ssl, des);
	return (tmp);
}
