/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 11:59:21 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/23 01:52:46 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

char	*base64_exe(t_ssl *ssl, char *in)
{
	char	*ret;
	char	*tmp;
	int		len;
	int		ret_len;

	len = ssl->in_size;
	if (ssl->flag->d)
	{
		tmp = whitespace_trim(in, &len);
		ret_len = 3 * (len / 4);
		tmp[len - 1] == '=' ? --ret_len : 0;
		tmp[len - 2] == '=' ? --ret_len : 0;
		ret = base64_decode(tmp, len, ret_len);
		free(tmp);
	}
	else
	{
		ret_len = 4 * ((len + 2) / 3);
		ret_len += ret_len >= 64 ? (ret_len % 64) : 0;
		NULL_GUARD(ret = ft_strnew(ret_len));
		base64_encode(in, len, ret, ret_len);
	}
	ssl->ou_size = ret_len;
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
	b.san = 0;
	j = -1;
	while (b.san < len)
	{
		i = -1;
		b.out_a = b.san < len ? (int)in[b.san++] : 0;
		b.out_b = b.san < len ? (int)in[b.san++] : 0;
		b.out_c = b.san < len ? (int)in[b.san++] : 0;
		b.out_d = (b.out_a << 16) | (b.out_b << 8) | b.out_c;
		while (++i < 4)
			ret[++j] = key[(b.out_d >> (18 - (6 * i))) & 0x3f];
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
	b.yon = 0;
	c = -1;
	while (b.yon < len)
	{
		b.out_a = in[b.yon] != '=' ? t[(int)in[b.yon++]] : 0 & ++b.yon;
		b.out_b = in[b.yon] != '=' ? t[(int)in[b.yon++]] : 0 & ++b.yon;
		b.out_c = in[b.yon] != '=' ? t[(int)in[b.yon++]] : 0 & ++b.yon;
		b.out_d = in[b.yon] != '=' ? t[(int)in[b.yon++]] : 0 & ++b.yon;
		b.out_e = (b.out_a << 18) + (b.out_b << 12) + (b.out_c << 6) + b.out_d;
		i = -1;
		while (++i < 3 && ++c < ret_len)
			ret[c] = (char)((b.out_e >> (16 - (8 * i))) & 0xff);
	}
	return (ret);
}

char	*whitespace_trim(char *in, int *len)
{
	char	*ret;
	int		i;
	int		j;

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
