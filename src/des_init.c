/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 21:38:22 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/25 21:34:49 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void		des_init(t_des *des)
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

void		des_pbkdf(t_ssl *ssl, t_des *des)
{
	char		*tmp;
	char		*out;
	int			i;

	if (!ssl->user_pass && (!ssl->user_key || !ssl->user_iv))
	{
		tmp = getpass("Enter encryption password:");
		ssl->user_pass = ft_strnew(32);
		ft_memcpy(ssl->user_pass, tmp, (i = ft_strlen(tmp)) <= 32 ? i : 32);
		ft_bzero(tmp, i);
		if (!ft_strnequ(ssl->user_pass,
			(tmp = getpass("Reenter for confirmation:")), i <= 32 ? i : 32))
			ft_error("Password confirmation failed.  Exiting.", 1);
		ft_bzero(tmp, i);
		while (i < 32)
			ssl->user_pass[i++] = '0';
		MATCH(!ssl->user_salt, ssl->user_salt = random_hex_str(16));
		des->nacl = hex_str_to_64bit(ssl->user_salt);
		out = append_hash_repeat(ssl->user_pass, des->nacl);
		ft_strtoupper(&out);
		MATCH(!ssl->user_key, ssl->user_key = ft_strndup(out, 16));
		MATCH(!ssl->user_iv, ssl->user_iv = ft_strndup(&out[16], 16));
		free(out);
	}
	des->key = blender(ssl->user_key);
}

void		des_subkeys(t_des *des, unsigned int r)
{
	uint64_t	kp;
	int			i;
	int			j;

	kp = perm_choice(des->key, des->pc1, 56);
	des->l[0] = DES_ROT((kp >> 28), des->shifts[0]);
	des->r[0] = DES_ROT((kp & 0xfffffff), des->shifts[0]);
	i = 0;
	while (++i < 16)
	{
		des->l[i] = DES_ROT(des->l[i - 1], des->shifts[i]);
		des->r[i] = DES_ROT(des->r[i - 1], des->shifts[i]);
	}
	i = -1;
	while (++i < 16)
	{
		j = !r ? i : 15 - i;
		kp = ((uint64_t)des->l[i] << 28) | (uint64_t)des->r[i];
		des->subkey[j] = perm_choice(kp, des->pc2, 48);
	}
}

uint64_t	perm_choice(uint64_t key, int *pc, int size)
{
	uint64_t	ret;
	int			i;

	i = -1;
	ret = 0;
	while (++i < size)
		ret |= (key >> (((size + 8) > 64 ? 64 : size + 8) - pc[i] & 1)) <<
			(size - (i + 1));
	return (ret);
}
