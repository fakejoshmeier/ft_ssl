/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 07:12:26 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/31 17:11:23 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

/*
** So openssl only hashes the password and salt once before deriving the keys.
** I'll follow that example.
*/

char	*a(char *pass, uint64_t salt)
{
	t_ssl	hash;
	char	*ret;
	char	*tmp;
	int		i;

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

	MATCH(ssl->user_pass, free(ssl->user_pass));
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
	free(des->p);
	free(des->fp);
}

/*
** So, basically, if the input is salted, I am going to demand a password.  I am
** also going to recalculate the key and IV, even though OpenSSL just takes the
** incorrect key input over the existence of a salt.  Granted, there is the
** chance that there is an unsalted output will somehow produce a perfect first
** 8 bits that say "Salted__".  And there is a chance that Warren Buffett will
** become my sugar daddy.
*/

void	extract_salt(t_ssl *ssl, char *in)
{
	uint64_t	test;
	char		*pass;
	char		*tmp;

	MATCH(!ft_strnequ(in, "Salted__", 8), ft_error("Bad magic number", 1));
	ft_memcpy(&test, &in[8], 8);
	if (!ssl->user_pass)
	{
		pass = getpass("enter decryption password:");
		ssl->user_pass = ft_strnew(ft_strlen(pass));
		ft_memcpy(ssl->user_pass, pass, ft_strlen(pass));
		ft_bzero(pass, ft_strlen(pass));
	}
	tmp = a(ssl->user_pass, test);
	ssl->user_key = ft_strndup(tmp, 16);
	ssl->user_iv = ft_strndup(&tmp[16], 16);
	free(tmp);
}
