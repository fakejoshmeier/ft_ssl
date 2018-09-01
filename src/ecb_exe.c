/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:54:16 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/31 17:35:10 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char		*ecb_exe(t_ssl *ssl, char *in)
{
	t_des		des;
	char		*ret;

	des_init(&des);
//	ret = ssl->flag->d ? ecb_decode(ssl, &des, in) : ecb_encode(ssl, &des, in);
	ret = ft_strdup(in);
	MATCH(ssl->user_pass, printf("Password:%s\n", ssl->user_pass));
	MATCH(ssl->user_salt, printf("Salt:%s\n", ssl->user_salt));
	MATCH(ssl->user_key, printf("Key:%s\n", ssl->user_key));
	MATCH(ssl->user_iv, printf("IV :%s\n", ssl->user_iv));
	free(in);
	des_clean(ssl, &des);
	return (ret);
}

char		*ecb_encode(t_des *des, t_ssl *ssl, char *in)
{
	char		*salted;
	char		*ret;
	char		*tmp;

	des_pbkdf(ssl, des, 1);
	des_subkeys(des, ssl->flag->d);
	des_pad(&in, &(ssl->in_size));
	ret = des_algo(in, ssl, des);
	if (ssl->user_pass)
	{
		salted = ft_strnew(16);
		ft_memcpy(salted, "Salted__", 8);
		ft_memcpy(&salted[8], &(des->nacl), 8);
		ssl->ou_size += 16;
		tmp = ft_strfjoin(salted, ret);
		free(ret);
		ret = tmp;
	}
	if (ssl->flag->a)
	{
		tmp = base64_exe(ssl, ret);
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
