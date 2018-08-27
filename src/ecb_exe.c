/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:54:16 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/26 10:37:00 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char		*ecb_exe(t_ssl *ssl, char *in)
{
	t_des		des;
	char		*ret;
	char		*tmp;

	des_init(&des);
	des_pbkdf(ssl, &des);
	if (ssl->flag->a && ssl->flag->d)
	{
		tmp = base64_exe(ssl, in);
		free(in);
		in = tmp;
	}
	if (!ssl->flag->d)
		des_pad(&in, &(ssl->in_size));
//	ret = ssl->flag->d ? ecb_decode(ssl, &des, in) : ecb_encode(ssl, &des, in);
	printf("Password:%s\nSalt:%s\nKey:%s\nIV:%s\n", ssl->user_pass,
		ssl->user_salt, ssl->user_key, ssl->user_iv);
	free(in);
	des_clean(ssl, &des);
	return (ret);
}
/*
char		*ecb_encode(t_des *des, t_ssl *ssl, char *in)
{
	char		*salted;
	char		*ret;

	salted = ft_strnew(16);
	salted = "Salted__";
	ft_memcpy(&salted[8], &(des->nacl));

	if (ssl->flag->a)
	{
		ret = base64_exe(ssl, in);
		ssl->in_size = ssl->ou_size;
	}
	return (ret);
}
*/
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

	if (ft_strnequ("Salted__", in, 8))
	{
		extract_salt(ssl, des, in);
		tmp = ft_strnew((ssl->in_size -= 16));
		ft_memcpy(&tmp, &in[16], ssl->in_size);
	}

	tmp = in;
	free(in);
	des_subkeys(des, ssl->flag->d);
	return (tmp);
}
