/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:54:16 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/01 15:25:35 by jmeier           ###   ########.fr       */
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

char		*ecb_encode(t_des *des, t_ssl *ssl, char *in)
{
	char		*salted;
	char		*ret;
	char		*tmp;
	int			i;

	des_pbkdf(ssl, des, 1);
	des_subkeys(des, ssl->flag->d);
	ssl->in_size += (ssl->in_size % 8 == 0) ? 8 : 0;
	ret = des_algo(in, ssl, des);
	if (ssl->user_pass)
	{
		salted = ft_strnew(16);
		ft_memcpy(salted, "Salted__", 8);
		i = -1;
		while (++i < 8)
			salted[8 + i] = (des->nacl >> (56 - (i * 8))) & 0xff;
		tmp = ft_strfjoin(salted, ret);
		free(ret);
		ret = tmp;
	}
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

	if (ssl->flag->a && ssl->flag->d)
	{
		tmp = base64_exe(ssl, in);
		free(in);
		in = tmp;
	}
	if (!ssl->flag->k)
	{
		extract_salt(ssl, in);
		tmp = ft_strnew((ssl->in_size -= 16));
		ft_memcpy(&tmp, &in[16], ssl->in_size);
		free(in);
		in = tmp;
	}
	des->key = blender(ssl->user_key);
	des_subkeys(des, ssl->flag->d);
	ret = des_algo(in, ssl, des);
	return (tmp);
}
