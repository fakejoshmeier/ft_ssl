/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 02:18:42 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/27 03:38:18 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	std_out(t_ssl *ssl, char *in, char *out)
{
	int		len;

	if (ssl->flag->p)
	{
		len = ft_strlen(in);
		write(1, in, len);
		if (len > 0 && in[len - 1] != '\n')
			write(1, "\n", 1);
	}
	write(1, out, ssl->ou_size);
	write(1, "\n", 1);
}

void	str_out(t_ssl *ssl, char *in, char *out)
{
	if (ssl->flag->q)
	{
		write(1, out, ssl->ou_size);
		write(1, "\n", 1);
	}
	else if (ssl->flag->r)
		ft_printf("%s \"%s\"\n", out, in);
	else
		ft_printf("%s (\"%s\") = %s\n", ssl->cmd, in, out);
}

void	file_out(t_ssl *ssl, char *out)
{
	if (ssl->flag->q)
	{
		write(1, out, ssl->ou_size);
		write(1, "\n", 1);
	}
	else if (ssl->flag->r)
		ft_printf("%s %s\n", out, ssl->filename);
	else
		ft_printf("%s (%s) = %s\n", ssl->cmd, ssl->filename, out);
}