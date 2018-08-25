/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:54:16 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/25 08:31:00 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char		*des_ecb_exe(t_ssl *ssl, char *in)
{
	t_des		des;
//	uint64_t
	char		*ret;

	des_init(&des);
	des_pbkdf(ssl, &des);
	des_subkeys(&des, ssl->flag->d);
	
	printf("Password:%s\nSalt:%s\nKey:%s\nIV:%s\n", ssl->user_pass, ssl->user_salt, ssl->user_key, ssl->user_iv);
	printf("%s", in);
	ret = ft_strnew(69);
//	des_clean(ssl, &des);
	return (ret);
}
/*
char		*des_ecb_encode(t_des *des, t_ssl *ssl, char *in)
{
	char		*ret;
	uint64_t	msg;

	//find 64 bit blocks
	g
	if (ssl->flag->a && !ssl->flag->d)
	{
		ret = base64_exe(ssl, in);
		ssl->in_size = ssl->ou_size;
	}
	return (ret);
}

void		des_ecb_clean(t_ssl *ssl, t_des *des)
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
	free(des->ebit);
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 4)
			free(des->s[i][j]);
	}
	free(des->p_table);
	free(des->inverse_table)
}
*/

