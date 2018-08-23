/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 20:47:11 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/23 03:07:36 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	set_val(char ***arg, char **value, unsigned int *flag)
{
	(*arg)++;
	*value = **arg;
	*flag = 1;
}

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
			ssl->str_in = (char **)ft_realloc(ssl->str_in, (sizeof(char *) *
				(i + 1)));
			set_val(av, &(ssl->str_in[i]), &(f->s));
			ssl->str_tot = ++i;
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
		MATCH(ft_strequ("-d", **av), f->d = 1);
		OR(ft_strequ("-e", **av), f->e = 1);
		OR(ft_strequ("-i", **av), set_val(av, &(ssl->filename), &(f->i)));
		OR(ft_strequ("-o", **av), set_val(av, &(ssl->ou_file), &(f->o)));

		(*av)++;
	}
	return (f);
}

t_flag	*des_flags(char ***av, t_ssl *ssl)
{
	t_flag	*f;
	char	***tmp;
	int		i;

	tmp = av;
	f = b64_flags(av, ssl);
	av = tmp;
	i = 0;
	while (**av && **av[0] == '-')
	{
		MATCH(ft_strequ("-a", **av), f->a = 1);
		OR(ft_strequ("-d", **av), f->d = 1);
		OR(ft_strequ("-e", **av), f->e = 1);
		OR(ft_strequ("-i", **av), set_val(av, &(ssl->filename), &(f->i)));
		OR(ft_strequ("-k", **av), set_val(av, &(ssl->user_key), &(f->k)));
		OR(ft_strequ("-o", **av), set_val(av, &(ssl->ou_file), &(f->o)));
		OR(ft_strequ("-p", **av), set_val(av, &(ssl->user_pass), &(f->p)));
		OR(ft_strequ("-s", **av), set_val(av, &(ssl->user_salt), &(f->s)));
		OR(ft_strequ("-v", **av), set_val(av, &(ssl->user_iv), &(f->v)));
		(*av)++;
	}
	return (f);
}
