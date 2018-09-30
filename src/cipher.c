/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 00:08:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/29 22:20:52 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	cipher(t_ssl *ssl)
{
	char	*in;
	char	*out;
	char	*tmp;

	in = ssl->flag->i ? file_in(ssl) : stdin_in(ssl);
	MATCH(!in, ft_error("ft_ssl: failed to get input", 1));
	if (ssl->flag->a && ssl->flag->d)
	{
		tmp = base64_exe(ssl, in);
		free(in);
		in = tmp;
		ssl->ou_size = 0;
	}
	out = ssl->exe(ssl, in);
	if (ssl->flag->a && !ssl->flag->d)
	{
		ssl->in_size = ssl->ou_size;
		tmp = base64_exe(ssl, out);
		free(out);
		out = tmp;
	}
	ssl->flag->o ? write_to_file(out, ssl->ou_file, ssl->ou_size) :
		write(1, out, ssl->ou_size);
	free(in);
	free(out);
}

int		write_to_file(char *out, char *file, size_t len)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		ft_error(file, 4);
	if ((write(fd, out, len) == -1))
		ft_error(file, 5);
	close(fd);
	return (0);
}
