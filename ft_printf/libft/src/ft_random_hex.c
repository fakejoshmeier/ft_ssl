/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:25:23 by jmeier            #+#    #+#             */
/*   Updated: 2018/10/22 19:35:24 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_str_to_hex(char *s)
{
	char		*hex_string;
	char		*hex;
	int			len;
	int			i;

	if ((len = ft_strlen(s)) == 0)
		return (0);
	len *= 2;
	if (!(hex_string = ft_strnew(len)))
		return (NULL);
	i = 0;
	hex = "0123456789ABCDEF";
	while (i < len)
	{
		hex_string[i++] = hex[((*s) >> 4) & 0xF];
		hex_string[i++] = hex[(*s) & 0xF];
		++s;
	}
	return (hex_string);
}

char		*ft_random_hex(int size)
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
		if (!(ret = ft_str_to_hex(buf)))
			return (close(fd) == 0 ? NULL : NULL);
	}
	close(fd);
	ret[size] = '\0';
	return (ret);
}
