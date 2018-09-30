/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:53:38 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/28 23:05:12 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*stdin_in(t_ssl *ssl)
{
	char	*tmp;
	char	*ret;
	char	buf[256];
	int		i;

	ret = ft_strnew(0);
	ssl->in_size = 0;
	while ((i = read(0, buf, 255)))
	{
		if (i == -1)
		{
			ft_printf("ft_ssl: read error: failed to read from stdin\n");
			free(ret);
			return (NULL);
		}
		NULL_GUARD(tmp = ft_strnew(i + ssl->in_size));
		ft_memcpy(tmp, ret, ssl->in_size);
		ft_memcpy(&tmp[ssl->in_size], buf, i);
		ssl->in_size += i;
		free(ret);
		ret = tmp;
	}
	return (ret);
}

char	*file_in(t_ssl *ssl)
{
	char	*ret;

	ssl->in_size = get_file_contents(ssl->filename, &ret);
	if (!ssl->in_size)
	{
		ft_printf("ft_ssl: %s: %s: No such file or directory\n", ssl->cmd_,
			ssl->filename);
		return (NULL);
	}
	return (ret);
}
