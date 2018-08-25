/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 00:08:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/23 17:01:58 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	cipher(t_ssl *ssl)
{
	char	*in;
	char	*out;

	in = ssl->flag->i ? file_in(ssl) : stdin_in(ssl);
	MATCH(!in, ft_error("ft_ssl: failed to get input", 1));
	out = ssl->exe(ssl, in);
	if (ssl->flag->o)
		write_to_file(out, ssl->ou_file, ssl->ou_size);
	else
	{
		write(1, out, ssl->ou_size);
		if (out[ssl->ou_size - 1] != '\n')
			write(1, "\n", 1);
	}
	free(in);
	free(out);
}

int		write_to_file(char *out, char *file, size_t len)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		ft_error(file, 4);
	if ((write(fd, out, strlen(out))) == -1)
		ft_error(file, 5);
	if (out[len - 1] != '\n')
		if (write(fd, "\n", 1) == -1)
			ft_error(file, 5);
	close(fd);
	return (0);
}
