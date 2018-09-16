/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 07:12:26 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/15 21:14:49 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

/*
** So openssl only hashes the password and salt once before deriving the keys.
** I'll follow that example.
*/

char		*a(char *pass, uint64_t salt)
{
	t_ssl		hash;
	char		*ret;
	char		*tmp;
	int			i;

	i = ft_strlen(pass);
	NULL_GUARD(tmp = ft_strnew(i + 8));
	hash.in_size = i + 8;
	ft_memcpy(tmp, pass, i);
	ft_memcpy(&tmp[i], &salt, 8);
	ret = md5_exe(&hash, tmp);
	free(tmp);
	tmp = NULL;
	ft_strtoupper(&ret);
	return (ret);
}

uint64_t	blender(char *key)
{
	uint64_t	ret;
	uint64_t	tmp;
	int			i;

	ret = 0;
	tmp = 0;
	i = -1;
	while ((tmp = key[++i]))
	{
		tmp -= tmp > 47 && tmp < 58 ? 48 : 0;
		tmp -= tmp > 64 && tmp < 71 ? 55 : 0;
		ret |= (tmp & 0xf) << (60 - (i * 4));
	}
	return (ret);
}

void		des_clean(t_ssl *ssl, t_des *des)
{
	int			i;
	int			j;

	MATCH(!ssl->flag->p && ssl->user_pass, free(ssl->user_pass));
	MATCH(ssl->user_salt, free(ssl->user_salt));
	MATCH(ssl->user_key, free(ssl->user_key));
	MATCH(ssl->user_iv, free(ssl->user_iv));
	free(des->pc1);
	free(des->pc2);
	free(des->shifts);
	free(des->init_perm);
	free(des->ebit);
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 4)
			free(des->s[i][j]);
	}
	free(des->p32);
	free(des->final_perm);
}

char		*des_enc_out(t_ssl *ssl, t_des *des)
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
	return (ret);
}
