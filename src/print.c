/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 02:18:42 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/25 04:26:44 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	std_out(t_ssl *ssl, char *in, char *out)
{
	int		len;

	if (ssl->f.p)
	{
		len = ft_strlen(in);
		write(1, in, len);
		if (len > 0 && in[len - 1] != '\n')
			write(1, "\n", 1);
	}
	ft_putendl(out);
}

void	str_out(t_ssl *ssl, char *in, char *out)
{
	if (ssl->f.q)
		ft_putendl(out);
	else if (ssl->f.r)
		ft_printf("%s \"%s\"\n", out, in);
	else
		ft_printf("%s (\"%s\") = %s\n", ssl->cmd, in, out);
}

void	file_out(t_ssl *ssl, char *out)
{
	if (ssl->f.q)
		ft_putendl(output);
	else if (ssl->f.r)
		ft_printf("%s %s\n", out, ssl->filename);
	else
		ft_printf("%s (%s) = %s\n", ssl->cmd, ssl->filename, out);
}