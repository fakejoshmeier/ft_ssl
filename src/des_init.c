/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 21:38:22 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/25 02:58:16 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	des_init(t_des *des)
{
	des->pc1 = ft_atoi_arr(PC1);
	des->pc2 = ft_atoi_arr(PC2);
	des->shifts = ft_atoi_arr(SHIFT_BY);
	des->init_perm = ft_atoi_arr(IP);
	des->ebit = ft_atoi_arr(EBIT);
	GET_S1;
	GET_S2;
	GET_S3;
	GET_S4;
	GET_S5;
	GET_S6;
	GET_S7;
	GET_S8;
	des->p_table = ft_atoi_arr(P_TABLE);
}

/*
** So.  PBKDF, or Password Based Key Derivation Function.  I need a password
** in the case of no key and iv.  If no password is provided, I prompt the user
** instead of making my own up or whatever.  That's all in the pdf at any rate.
** So, the way it works is, with the password, I append a randomly conjured
** salt, then hash the password + salt however many times
*/

void	des_pbkdf(t_ssl *ssl, t_des *des)
{
	uint64_t	s;
	char		*tmp;
	char		*out;
	int			i;

	if (!ssl->user_pass && (!ssl->user_key || !ssl->user_iv))
	{
		tmp = getpass("Enter password:");
		ssl->user_pass = ft_strnew(32);
		ft_memcpy(ssl->user_pass, tmp, (i = ft_strlen(tmp)) <= 32 ? i : 32);
		ft_bzero(tmp, i);
		while (i < 32)
			ssl->user_pass[i++] = '0';
		MATCH(!ssl->user_salt, ssl->user_salt = random_hex_str(16));
		s = hex_str_to_64bit(ssl->user_salt);
		out = append_hash_repeat(ssl->user_pass, s);
		ft_strtoupper(&out);
		MATCH(!ssl->user_key, ssl->user_key = ft_strndup(out, 16));
		MATCH(!ssl->user_iv, ssl->user_iv = ft_strndup(&out[16], 16));
		free(out);
	}
	des->key = blender(ssl->user_key);
}

/*
** So openssl only hashes the password and salt once before deriving the keys.
** I'll follow that example.
*/

char	*append_hash_repeat(char *pass, uint64_t salt)
{
	t_ssl	hash;
	char	*ret;
	char	*tmp;

	NULL_GUARD(tmp = ft_strnew(40));
	hash.in_size = 40;
	ft_memcpy(tmp, pass, 32);
	ft_memcpy(&tmp[32], &salt, 8);
	ret = md5_exe(&hash, tmp);
	free(tmp);
	tmp = NULL;
	return (ret);
}

