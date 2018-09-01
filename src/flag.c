/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 20:47:11 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/30 10:27:41 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	set_val(char ***arg, char **value, unsigned int *flag, int len)
{
	char	*tmp;
	int		i;
	int		j;

	(*arg)++;
	MATCH(!(*arg), ft_error("ft_ssl: no arg for flag that requires arg", 1));
	if (len)
	{
		tmp = ft_strnew(len);
		i = ft_strlen(**arg);
		j = 0;
		ft_strncpy(tmp, **arg, i < len ? i : len);
		if (len == 16)
		{
			while (j < (i < len ? i : len))
				MATCH(!ft_ishex(tmp[j++]), ft_error("Invalid Key/IV/Salt", 1));
			ft_strtoupper(&tmp);
			while (i < len)
				tmp[i++] = '0';
		}
		*value = tmp;
	}
	else
		*value = **arg;
	*flag = 1;
}

t_flag	*md_flags(char ***av, t_ssl *ssl)
{
	t_flag	*f;
	int		i;

	NULL_GUARD(f = (t_flag *)ft_memalloc(sizeof(t_flag)));
	i = 0;
	while (**av && **av[0] == '-')
	{
		if (ft_strequ(**av, "-s"))
		{
			ssl->str_in = (char **)ft_realloc(ssl->str_in, (sizeof(char *) *
				(i + 1)));
			set_val(av, &(ssl->str_in[i]), &(f->s), 0);
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

	NULL_GUARD(f = (t_flag *)ft_memalloc(sizeof(t_flag)));
	while (**av)
	{
		MATCH(ft_strequ("-d", **av), f->d = 1);
		OR(ft_strequ("-e", **av), f->e = 1);
		OR(ft_strequ("-i", **av), set_val(av, &(ssl->filename), &(f->i), 0));
		OR(ft_strequ("-o", **av), set_val(av, &(ssl->ou_file), &(f->o), 0));
		OTHERWISE(ft_error(**av, 7));
		(*av)++;
	}
	return (f);
}

t_flag	*des_flags(char ***av, t_ssl *ssl)
{
	t_flag	*f;

	NULL_GUARD(f = (t_flag *)ft_memalloc(sizeof(t_flag)));
	while (**av)
	{
		MATCH(SE("-a", **av), f->a = 1);
		OR(SE("-d", **av), f->d = 1);
		OR(SE("-e", **av), f->e = 1);
		OR(SE("-i", **av), set_val(av, &(ssl->filename), &(f->i), 0));
		OR(SE("-k", **av), set_val(av, &(ssl->user_key), &(f->k), 16));
		OR(SE("-o", **av), set_val(av, &(ssl->ou_file), &(f->o), 0));
		OR(SE("-p", **av), set_val(av, &(ssl->user_pass), &(f->p), 32));
		OR(SE("-s", **av), set_val(av, &(ssl->user_salt), &(f->s), 16));
		OR(SE("-v", **av), set_val(av, &(ssl->user_iv), &(f->v), 16));
		OTHERWISE(ft_error(**av, 8));
		(*av)++;
	}
	return (f);
}
