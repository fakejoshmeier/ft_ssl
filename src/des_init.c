/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 21:38:22 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/06 18:48:41 by jmeier           ###   ########.fr       */
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
	des->p32 = ft_atoi_arr(P_TABLE);
	des->final_perm = ft_atoi_arr(FP);
}

/*
** So.  PBKDF, or Password Based Key Derivation Function.  I need a password
** in the case of no key and iv.  If no password is provided, I prompt the user
** and ask for confirmation.
** So, the way it works is, with the password, I append a randomly conjured
** salt, then hash the password + salt however many times.  In the case of
** OpenSSL, it's once.
*/

void		des_pbkdf(t_ssl *ssl, t_des *des, char **in)
{
	char		*tmp;
	int			i;

	if (!ssl->flag->k && !ssl->user_pass)
	{
		tmp = !ssl->flag->d ? getpass("Enter encryption password:") :
			getpass("Enter decryption password:");
		ssl->user_pass = ft_strnew(ft_strlen(tmp));
		ft_memcpy(ssl->user_pass, tmp, (i = ft_strlen(tmp)));
		ft_bzero(tmp, i);
		if (!ssl->flag->d && !ft_strnequ(ssl->user_pass,
			(tmp = getpass("Reenter for confirmation:")), i))
			ft_error("Password confirmation failed.  Exiting.", 1);
		ft_bzero(tmp, i);
		free(tmp);
		ft_strclean(ssl->user_pass);
	}
	MATCH(!ssl->user_salt, ssl->user_salt = rand_hex_str(16));
	des->nacl = ssl->flag->d ? extract_salt(ssl, in) :
		hex_str_to_64bit(ssl->user_salt);
	MATCH(ssl->user_pass, tmp = a(ssl->user_pass, des->nacl));
	MATCH(!ssl->user_key && tmp, ssl->user_key = ft_strndup(tmp, 16));
	MATCH(!ssl->user_iv && tmp, ssl->user_iv = ft_strndup(&tmp[16], 16));
	MATCH(ssl->user_pass, free(tmp));
	des->key = blender(ssl->user_key);
}

/*
** For OpenSSL, a DES ciphered output that has also been salted will have 16
** bytes at the front.  The first eight will be "Salted__", followed by the 8
** bit long salt.  This function checks for the salt in the case of no key being
** provided.  If there is a key, the salt isn't necessary.  Anyway, I get the
** salt and life goes on.
*/

uint64_t	extract_salt(t_ssl *ssl, char **in)
{
	uint64_t	test;

	if (ssl->flag->k)
		return (0);
	MATCH(!ft_strnequ(*in, "Salted__", 8), ft_error("Bad magic number", 1));
	ft_memcpy(&test, &(*in)[8], 8);
	ssl->in_size -= 16;
	*in += 16;
	return (test);
}

/*
** The DES algorithm is the same for decrypting as it is encrypting, but the
** final permutation is applied to the key in reverse.  Thanks to the magic of
** math and indices, it's not too difficult to do.
*/

void		des_subkeys(t_des *des, unsigned int r, uint64_t chi)
{
	uint64_t	perm_key;
	int			i;
	int			j;

	perm_key = permute_key_by_x_for_y(chi, des->pc1, 56);
	des->l[0] = DES_ROT((perm_key >> 28), des->shifts[0]);
	des->r[0] = DES_ROT((perm_key & 0xfffffff), des->shifts[0]);
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
		perm_key = ((uint64_t)des->l[i] << 28) | (uint64_t)des->r[i];
		des->subkey[j] = permute_key_by_x_for_y(perm_key, des->pc2, 48);
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
		ret |= (key >> (MIN((size + 8), 64) - pc[i]) & 1) << (size - (i + 1));
	return (ret);
}
