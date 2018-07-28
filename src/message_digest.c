/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_digest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 23:12:01 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/28 00:57:31 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	message_digest(t_ssl *ssl)
{
	if ((!ssl->file_in && !ssl->str_in && !ssl->flag->p) || ssl->flag->p == 1)
		message_digest_print(ssl, stdin_in(ssl), 1);
	if (ssl->str_in)
		message_digest_str(ssl);
	if (ssl->file_in)
		message_digest_file(ssl);
	if (*(ssl->str_in))
	{
		free(ssl->str_in);
		ssl->str_in = NULL;
	}
}

void	message_digest_print(t_ssl *ssl, char *in, int id)
{
	char	*out;

	if (!in)
		return ;
	out = ssl->exe(ssl, in);
	if (id == 1)
		std_out(ssl, in, out);
	else if (id == 2)
		str_out(ssl, in, out);
	else if (id == 3)
		file_out(ssl, out);
	free(in);
	free(out);
	in = NULL;
	out = NULL;
}

void	message_digest_str(t_ssl *ssl)
{
	int		i;
	char	*in;

	i = -1;
	while (++i < ssl->str_tot)
	{
		ssl->str_curr = ssl->str_in[i];
		in = ft_strdup(ssl->str_curr);
		ssl->in_size = ft_strlen(in);
		message_digest_print(ssl, in, 2);
	}
}

void	message_digest_file(t_ssl *ssl)
{
	int		i;
	char	*in;

	i = -1;
	while (ssl->file_in[++i])
	{
		ssl->filename = ssl->file_in[i];
		in = file_in(ssl);
		if (in)
			message_digest_print(ssl, in, 3);
	}
}
