/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 17:01:27 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/28 21:33:02 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

t_flag	*read_flags(char ***av, char *valid, t_ssl *ssl)
{
	t_flag	*f;
	int		i;

	f = (t_flag *)ft_memalloc(sizeof(t_flag));
	i = 0;
	while (**av && **av[0] == '-')
	{
		if (ft_strequ(**av, "-s") && ft_strstr(valid, "-p"))
		{
			f->s = 1;
			(*av)++;
			ssl->str_in = (char **)ft_realloc(ssl->str_in, (sizeof(char *) *
				(i + 1)));
			ssl->str_in[i++] = **av;
			ssl->str_tot = i;
		}
		OR(ft_strequ("-p", **av) && ft_strstr(valid, "-p"), f->p = 1);
		OR(ft_strequ("-q", **av) && ft_strstr(valid, "-q"), f->q = 1);
		OR(ft_strequ("-r", **av) && ft_strstr(valid, "-r"), f->r = 1);
		OTHERWISE(ft_error(**av, 3));
		(*av)++;
	}
	MATCH(**av, ssl->file_in = *av);
	return (f);
}

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
	if (i == 3)
	{
		ft_printf("unknown option '%s'\noptions are\n-p\techo STDIN to ", str);
		ft_printf("STDOUT and append the checksum to STDOUT\n-q\tquiet mode");
		ft_printf("\n-r\treverse the format of the output\n-s\tprint the sum");
		ft_putendl(" of the given string");
	}
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
	ssl.flag = read_flags(&av, ssl.valid_flags, &ssl);
	ssl.cmd(&ssl);
	free(ssl.flag);
	ssl.flag = NULL;
	return (0);
}
