/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 07:12:26 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/26 00:43:27 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

/*
** So openssl only hashes the password and salt once before deriving the keys.
** I'll follow that example.
*/

char	*append_hash_repeat(char *pass, uint64_t salt)
{
	t_ssl	hash;
	char	*ret;
	char	*tmp;
	uint64_t	test;

	NULL_GUARD(tmp = ft_strnew(40));
	hash.in_size = 40;
	ft_memcpy(tmp, pass, 32);
	ft_memcpy(&tmp[32], &salt, 8);
	ft_memcpy(&test, &tmp[32], 8);
	ret = md5_exe(&hash, tmp);
	free(tmp);
	tmp = NULL;
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

	free(ssl->user_pass);
	free(ssl->user_salt);
	free(ssl->user_key);
	free(ssl->user_iv);
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
	free(des->p_table);
//	free(des->inverse_table);
}

void	extract_salt(t_ssl *ssl, t_des *des, char *in)
{
	uint64_t	test;
	char		*tmp;

	ft_memcpy(&test, &in[8], 8);
	if (test != des->nacl)
	{
		free(ssl->user_key);
		free(ssl->user_iv);
		tmp = append_hash_repeat(ssl->user_pass, test);
		ssl->user_key = ft_strndup(tmp, 16);
		ssl->user_iv = ft_strndup(&tmp[16], 16);
		free(tmp);
		des->key = blender(ssl->user_key);
	}
}
