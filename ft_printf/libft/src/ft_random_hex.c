/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:25:23 by jmeier            #+#    #+#             */
/*   Updated: 2018/10/22 16:27:05 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*random_hex(int size)
{
	char		*ret;
	char		buf[2 + (size / 2)];
	int			res;
	int			fd;
	int			buf_size;

	ret = ft_strnew(size - 1);
	buf_size = (size / 2) ? (size / 2) : 1;
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		return (NULL);
	while (ft_strlen(ret) != size)
	{
		free(ret);
		res = read(fd, buf, buf_size);
		if (res < buf_size || (buf[buf_size] = 0))
			return (close(fd) == 0 ? NULL : NULL);
		if (!(ret = str_to_hex(buf)))
			return (close(fd) == 0 ? NULL : NULL);
	}
	close(fd);
	ret[size] = '\0';
	return (ret);
}
