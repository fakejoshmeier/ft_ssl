/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 11:59:21 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/15 19:53:04 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*base64_exe(t_ssl *ssl, char *in)
{
	char	*ret;
	char	*tmp;
	int		ret_len;

	if (ssl->flag->d)
	{
		tmp = whitespace_trim(in, &(ssl->in_size));
		ret_len = 3 * (ssl->in_size / 4);
		tmp[ssl->in_size - 1] == '=' ? --ret_len : 0;
		tmp[ssl->in_size - 2] == '=' ? --ret_len : 0;
		ret = base64_decode(tmp, ssl->in_size, ret_len);
		free(tmp);
	}
	else
	{
		ret_len = 4 * ((ssl->in_size + 2) / 3);
		ret_len += ret_len >= 64 ? (ret_len / 64) : 0;
		NULL_GUARD(ret = ft_strnew(ret_len));
		base64_encode(in, ssl->in_size, ret, ret_len);
	}
	ssl->in_size = ret_len;
	ssl->ou_size = ret_len;
	free(in);
	return (ret);
}

/*
** The encode takes each char as an int in groups of three, ORs the chars
** into a 24 bit number, which is chopped up into four 6 bit pieces and each
** piece becomes an index on the B64 key string.  The character at the index is
** then added into the returning string.  At the end of the loop, it checks
** to add '=' signs in.  The '=' are just padding to show that the original
** input length was not properly divisible by three.
*/

void	base64_encode(char *in, int len, char *ret, int ret_len)
{
	t_b64		b;
	char		*key;
	int			i;
	int			j;

	key = B64;
	ft_bzero(&b, sizeof(t_b64));
	j = -1;
	while (b.iter < len)
	{
		i = -1;
		b.out_a = b.iter < len ? (uint8_t)in[b.iter++] : 0;
		b.out_b = b.iter < len ? (uint8_t)in[b.iter++] : 0;
		b.out_c = b.iter < len ? (uint8_t)in[b.iter++] : 0;
		b.out_d = (b.out_a << 16) | (b.out_b << 8) | b.out_c;
		while (++i < 4)
		{
			ret[++j] = key[(b.out_d >> (18 - (6 * i))) & 0x3f];
			b.out_e += 1;
			MATCH(b.out_e == 64, ret[++j] = '\n');
			MATCH(b.out_e == 64, b.out_e = 0);
		}
	}
	ret[ret_len - 1] = !b.out_c ? '=' : ret[ret_len - 1];
	ret[ret_len - 2] = !b.out_b ? '=' : ret[ret_len - 2];
}

/*
** Okay, same deal as the encode.  Every 4 letters becomes a letter
** corresponding to the key.  They all get OR'd into a 24 bit number
** and that number is chopped and screwed into chunks of three that
** coincidentally become ascii values for chars.  Also, made sure to
** trim for any sort of whitespace in the input.
*/

char	*base64_decode(char *in, int len, int ret_len)
{
	t_b64	b;
	char	*ret;
	int		*t;
	int		c;
	int		i;

	NULL_GUARD(t = decrypt_ref_table());
	NULL_GUARD(ret = ft_strnew(ret_len));
	b.iter = 0;
	c = -1;
	while (b.iter < len)
	{
		b.out_a = in[b.iter] != '=' ? t[(uint8_t)in[b.iter++]] : 0 & ++b.iter;
		b.out_b = in[b.iter] != '=' ? t[(uint8_t)in[b.iter++]] : 0 & ++b.iter;
		b.out_c = in[b.iter] != '=' ? t[(uint8_t)in[b.iter++]] : 0 & ++b.iter;
		b.out_d = in[b.iter] != '=' ? t[(uint8_t)in[b.iter++]] : 0 & ++b.iter;
		b.out_e = (b.out_a << 18) + (b.out_b << 12) + (b.out_c << 6) + b.out_d;
		i = -1;
		while (++i < 3 && ++c < ret_len)
			ret[c] = (char)((b.out_e >> (16 - (8 * i))) & 0xff);
	}
	return (ret);
}

char	*whitespace_trim(char *in, size_t *len)
{
	char	*ret;
	size_t	i;
	size_t	j;

	NULL_GUARD((ret = ft_memalloc(*len + 3)));
	i = 0;
	j = 0;
	while (j < *len)
	{
		if (ft_isspace(in[j]))
			j++;
		else
			ret[i++] = in[j++];
	}
	ret[i] = '\0';
	(*len) = i;
	return (ret);
}

int		*decrypt_ref_table(void)
{
	static int	ret[256];
	char		*key;
	int			i;

	key = B64;
	i = -1;
	while (++i < 64)
		ret[(int)key[i]] = i;
	return (ret);
}
