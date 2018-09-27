/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 22:54:12 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/27 01:08:32 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

t_flag	*ecb3_flags(char ***av, t_ssl *ssl)
{
	t_flag	*f;

	NULL_GUARD(f = (t_flag *)ft_memalloc(sizeof(t_flag)));
	while (**av)
	{
		MATCH(SE("-a", **av), f->a = 1);
		OR(SE("-d", **av), f->d = 1);
		OR(SE("-e", **av), f->e = 1);
		OR(SE("-i", **av), set_val(av, &(ssl->filename), &(f->i), 0));
		OR(SE("-k", **av), set_val(av, &(ssl->user_key), &(f->k), 48));
		OR(SE("-o", **av), set_val(av, &(ssl->ou_file), &(f->o), 0));
		OR(SE("-p", **av), set_val(av, &(ssl->user_pass), &(f->p), 0));
		OR(SE("-s", **av), set_val(av, &(ssl->user_salt), &(f->s), 16));
		OTHERWISE(ft_error(**av, 8));
		(*av)++;
	}
	ssl->triple = 1;
	return (f);
}
