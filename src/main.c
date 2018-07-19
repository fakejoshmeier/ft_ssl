/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:01:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/18 23:10:10 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	ft_error(char *str, int i)
{
	if (i == 1)
		ft_putendl(str);
	if (i == 2)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", str);
		ft_putendl("Standard commands:\n");
		ft_putendl("Message Digest commands:\nmd5\nsha256\n");
		ft_putendl("Cipher commands:");
	}
	exit(1);
}

int		main(int ac, char *av[])
{
	t_ssl	ssl;

	if (ac == 1)
		ft_error(USAGE, 1);
	ft_bzero(&ssl, (sizeof(t_ssl)));
	//if (!read_commands(av + 1, &ssl))
//		ft_error(av[1], 2);
//	do the studd
	ssl.in_size = ft_strlen(av[1]);
	char *fuck = exe_md5(&ssl, av[1]);
	ft_putendl(fuck);
	return (0);
}
