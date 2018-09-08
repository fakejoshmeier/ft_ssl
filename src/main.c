/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:01:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/03 15:31:07 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	**pull_from_stdin(void)
{
	t_ssl	tmp;
	char	**ret;
	char	*s;

	ft_bzero(&tmp, sizeof(t_ssl));
	s = stdin_in(&tmp);
	ret = ft_strsplit(s, ' ');
	free(s);
	s = NULL;
	return (ret);
}

void	ft_error(char *str, int i)
{
	MATCH(i == 1, ft_putendl(str));
	OR(i == 2, ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n\
Standard commands:\nMessage Digest commands:\nmd5\nsha224\nsha256\nsha384\n\
sha512\n\nCipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\n", str));
	OR(i == 3, ft_printf("unknown option '%s'\noptions are\n-p\techo STDIN to\
STDOUT and append the checksum to STDOUT\n-q\tquiet mode\n-r\treverse the \
format of the output\n-s\tprint the sum of the given string\n", str));
	OR(i == 4, ft_printf("ft_ssl: Unable to open/create file %s\n", str));
	OR(i == 5, ft_printf("ft_ssl: Unable to write to file %s\n", str));
	OR(i == 6, ft_printf("ft_ssl: %s - Invalid flag option\n", str));
	OR(i == 7, ft_printf("unknown option '%s'\noptions are\n-d\tdecode mode\
\n-e\tencode mode (default)\n-i\tinput file\n-o\toutput file\n", str));
	OR(i == 8, ft_printf("unknown option '%s'\noptions are\n-a\tdecode/encode \
the input/output in base64, depending on encrypt mode\n-d\tdecrypt mode\n-e\t\
-i\tinput file for message\n-k\tkey in hex is the next argument\n-o\toutput \
file for message\n-p\tpassword in ascii is the next argument\n-s\tthe salt in \
hex is the next argument\n-v\tinitialization vector in hex is the next argument\
\n", str));
	OR(i == 9, ft_printf("%s: No provided password, key, IV, or salt\n", str));
	exit(1);
}

int		main(int ac, char *av[])
{
	t_ssl	ssl;

	MATCH(ac < 2, ft_error(USAGE, 1));
	ft_bzero(&ssl, (sizeof(t_ssl)));
	av += 1;
	if (!read_commands(av, &ssl))
		ft_error(*av, 2);
	av += 1;
	MATCH(!(ssl.flag = ssl.fla(&av, &ssl)), ft_error("Flag failure", 1));
	ssl.cmd(&ssl);
	free(ssl.flag);
	ssl.flag = NULL;
	return (0);
}
