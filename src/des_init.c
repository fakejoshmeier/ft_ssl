/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 21:38:22 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/31 17:09:21 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void		des_init(t_des *des)
{
	ft_bzero(des, sizeof(t_des));
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
	des->p = ft_atoi_arr(P_TABLE);
	des->fp = ft_atoi_arr(FP);
}

/*
** So.  PBKDF, or Password Based Key Derivation Function.  I need a password
** in the case of no key and iv.  If no password is provided, I prompt the user
** instead of making my own up or whatever.  That's all in the pdf at any rate.
** So, the way it works is, with the password, I append a randomly conjured
** salt, then hash the password + salt however many times
**
** I don't believe there's a problem with this?
*/

void		des_pbkdf(t_ssl *ssl, t_des *des, int f)
{
	char		*tmp;
	int			i;

	if (((f == 1 && !ssl->flag->k) || (!f && !ssl->flag->k && !ssl->flag->v)) &&
		!ssl->user_pass)
	{
		tmp = getpass("Enter encryption password:");
		ssl->user_pass = ft_strnew(32);
		ft_memcpy(ssl->user_pass, tmp, (i = ft_strlen(tmp)) <= 32 ? i : 32);
		ft_bzero(tmp, i);
		if (!ft_strnequ(ssl->user_pass,
			(tmp = getpass("Reenter for confirmation:")), i <= 32 ? i : 32))
			ft_error("Password confirmation failed.  Exiting.", 1);
		ft_bzero(tmp, i);
		free(tmp);
		ft_strclean(ssl->user_pass);
	}
	MATCH(!ssl->user_salt, ssl->user_salt = rand_hex_str(16));
	des->nacl = hex_str_to_64bit(ssl->user_salt);
	MATCH(ssl->user_pass, tmp = a(ssl->user_pass, des->nacl));
	MATCH(!ssl->user_key && tmp, ssl->user_key = ft_strndup(tmp, 16));
	MATCH(!ssl->user_iv && tmp, ssl->user_iv = ft_strndup(&tmp[16], 16));
	MATCH(ssl->user_pass, free(tmp));
	des->key = blender(ssl->user_key);
}

/*
** The DES algorithm is the same for decrypting as it is encrypting, but the
** final permutation is applied to the key in reverse.  Thanks to the magic of
** math and indices, it's not too difficult to do.
*/

void		des_subkeys(t_des *des, unsigned int r)
{
	uint64_t	kp;
	int			i;
	int			j;

	kp = permute_key_by_x_for_y(des->key, des->pc1, 56);
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
		des->subkey[j] = permute_key_by_x_for_y(kp, des->pc2, 48);
	}
}

/*
** In the examples I've read, it appears that the algorithm runs on a little
** endian looking interpretation.  Hence why I shift by 64 - x, rather than x.
*/

uint64_t	permute_key_by_x_for_y(uint64_t key, int *pc, int size)
{
	uint64_t	ret;
	int			i;

	i = -1;
	ret = 0;
	while (++i < size)
		ret |= (key >> (MIN(size + 8, 64) - pc[i]) & 1) << (size - (i + 1));
	return (ret);
}
