/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 20:47:11 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/23 00:14:52 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

t_flag	*md_flags(char ***av, t_ssl *ssl)
{
	t_flag	*f;
	int		i;

	f = (t_flag *)ft_memalloc(sizeof(t_flag));
	i = 0;
	while (**av && **av[0] == '-')
	{
		if (ft_strequ(**av, "-s"))
		{
			f->s = 1;
			(*av)++;
			ssl->str_in = (char **)ft_realloc(ssl->str_in, (sizeof(char *) *
				(i + 1)));
			ssl->str_in[i++] = **av;
			ssl->str_tot = i;
		}
		OR(ft_strequ("-p", **av), f->p = 1);
		OR(ft_strequ("-q", **av), f->q = 1);
		OR(ft_strequ("-r", **av), f->r = 1);
		OTHERWISE(ft_error(**av, 3));
		(*av)++;
	}
	MATCH(**av, ssl->file_in = *av);
	return (f);
}

t_flag	*b64_flags(char ***av, t_ssl *ssl)
{
	t_flag	*f;
	int		i;

	f = (t_flag *)ft_memalloc(sizeof(t_flag));
	i = 0;
	while (**av && **av[0] == '-')
	{
		if (ft_strequ("-i", **av))
		{
			f->i = 1;
			(*av)++;
			ssl->filename = **av;
		}
		else if (ft_strequ("-o", **av))
		{
			f->o = 1;
			(*av)++;
			ssl->ou_file = **av;
		}
		OR(ft_strequ("-e", **av), f->e = 1);
		OR(ft_strequ("-d", **av), f->d = 1);
		(*av)++;
	}
	return (f);
}
