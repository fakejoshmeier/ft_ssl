/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 04:54:33 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/29 01:20:35 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char		*str_to_hex(char *s)
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

char		*random_hex_str(int size)
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

char		convert_hex_char_to_4bit(uint8_t c)
{
	if (c > 47 && c < 58)
		return (c - 48);
	else if (c > 64 && c < 71)
		return (c - 55);
	else if (c > 96 && c < 103)
		return (c - 97);
	return (0);
}

uint64_t	hex_str_to_64bit(char *s)
{
	uint64_t	ret;
	uint64_t	tmp;
	int			i;

	if (!s)
		return (0);
	i = -1;
	ret = 0;
	while (*s && ++i < 8)
	{
		tmp = ((uint64_t)convert_hex_char_to_4bit(*s)) << 4;
		++s;
		if (*s)
			tmp |= (uint64_t)convert_hex_char_to_4bit(*s);
		ret |= tmp << (8 * i);
		if (*s)
			++s;
	}
	return (ret);
}

uint64_t	des_str_to_64bit(char **input)
{
	uint8_t		i;
	uint64_t	message;
	uint64_t	remaining;

	i = -1;
	message = 0;
	while (++i < 8 && **input)
	{
		message |= ((uint64_t)(**input) << (56 - (i * 8)));
		++(*input);
	}
	remaining = 8 - i;
	while (i < 8)
	{
		message |= (remaining << (56 - (i * 8)));
		++i;
	}
	return (message);
}
