/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:01:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/23 03:04:13 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	ft_error(char *str, int i)
{
	MATCH(i == 1, ft_putendl(str));
	else if (i == 2)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", str);
		ft_putendl("Standard commands:\n");
		ft_putendl("Message Digest commands:\nmd5\nsha224\nsha256\nsha384");
		ft_putendl("sha512\n");
		ft_putendl("Cipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc");
	}
	else if (i == 3)
	{
		ft_printf("unknown option '%s'\noptions are\n-p\techo STDIN to ", str);
		ft_printf("STDOUT and append the checksum to STDOUT\n-q\tquiet mode");
		ft_printf("\n-r\treverse the format of the output\n-s\tprint the sum");
		ft_putendl(" of the given string");
	}
	OR(i == 4, ft_printf("ft_ssl: Unable to open/create file %s\n", str));
	OR(i == 5, ft_printf("ft_ssl: Unable to write to file %s\n", str));
	OR(i == 6, ft_printf("ft_ssl: %s - Invalid flag option\n", str));
	exit(1);
}

int		main(int ac, char *av[])
{
	t_ssl	ssl;

	if (ac == 1)
		ft_error(USAGE, 1);
	ft_bzero(&ssl, (sizeof(t_ssl)));
	av += 1;
	if (!read_commands(av, &ssl))
		ft_error(*av, 2);
	av += 1;
	ssl.flag = ssl.fla(&av, &ssl);
	ssl.cmd(&ssl);
	free(ssl.flag);
//	ssl.flag = (t_flag *)ft_memalloc(sizeof(t_flag));
//	printf("%s\n", base64_exe(&ssl, "foobar"));
//	ssl.flag->d = 1;
//	printf("%s\n", base64_exe(&ssl, "SnVnZW11IEp1Z2VtdSBHb2tvLW5vIHN1c\nmlraXJlIEthaWphcmlzdWlneW8tbm8gU3VpZ3lv\nbWF0c3UgVW5yYWltYXRzdSBGdXJhaW1hdHN1IEt1dW5lcnV0b2tvcm8tbmkgU3VtdXRva29ybyBZYWJ1cmFrb2ppLW5vIGJ1cmFrb2ppIFBhaXBvcGFpcG8gUGFpcG8tbm8tc2h1cmluZ2FuIFNodXJpbmdhbi1ubyBHdXJpbmRhaSBHdXJpbmRhaS1ubyBQb25wb2tvcGktbm8gUG9ucG9rb25hLW5vIENob2t5dW      1laS1ubyBDaG9zdWtl"));
	ssl.flag = NULL;
	return (0);
}
