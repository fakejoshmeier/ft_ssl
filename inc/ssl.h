/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:37:10 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/23 00:03:46 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H
# include <libft.h>
# include <ft_printf.h>
# include <limits.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# define USAGE "usage: ft_ssl command [command opts] [command args]"
# define MD5_F1(b, c, d) ((b & c) | ((~b) & d))
# define MD5_F2(b, c, d) ((d & b) | ((~d) & c))
# define MD5_F3(b, c, d) (b ^ c ^ d)
# define MD5_F4(b, c, d) (c ^ (b | (~d)))
# define LEFT_ROT(x, c) ((x << c) | (x >> (32 - c)))
# define RITE_ROT(x, c) ((x >> c) | (x << (32 - c)))

// typedef struct		s_node
// {
// 	char			*name;
// 	t_node			*next;
// }					t_node;

// typedef struct		s_stack
// {
// 	t_node			*top;
// }					t_stack;
typedef union		u_bit62
{
	uint64_t		init;
	uint32_t		piece[2];
	uint16_t		chunk[4];
	uint8_t			nugget[8];
}					t_u64;

typedef union		u_bit32
{
	uint32_t		init;
	uint16_t		chunk[2];
	uint8_t			nugget[4];
}					t_u32;

typedef struct		s_sha
{
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;
	uint32_t		h4;
	uint32_t		h5;
	uint32_t		h6;
	uint32_t		h7;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		t1;
	uint32_t		t2;
	uint32_t		k[64];
	uint32_t		w[64];
	uint8_t			*msg;
}					t_sha;

typedef struct		s_md5
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		a2;
	uint32_t		b2;
	uint32_t		c2;
	uint32_t		d2;
	uint32_t		f;
	uint32_t		g;
	uint32_t		m[16];
	uint32_t		s[64];
	uint32_t		k[64];
	uint8_t			*msg;
}					t_md5;

typedef struct		s_flag
{
	unsigned int	p;
	unsigned int	q;
	unsigned int	r;
	unsigned int	s;
}					t_flag;

typedef struct		s_ssl
{
	size_t			in_size;
	size_t			ou_size;
	char			**stdin_input;
	char			**file_input;
	char			**string_input;
	int				run;
	t_flag			*flag;
	t_md5			*md5;
//	void			*exe(*t_ssl);
//	void			*enc(*t_ssl);
}					t_ssl;
/*
** Endian functions
*/

uint64_t	b_endian64(uint64_t num);
int			check_endianness(void);

/*
** MD5 Functions
*/

char	*md5_exe(t_ssl *ssl, char *input);
void	md5_init(t_md5 *md, int i);
void	md5_init2(t_md5 *md, int i);
void	md5_hex(t_md5 *md5);
void	md5_hex1(t_md5 *md5);
void	md5_hex2(t_md5 *md5);
void	md5_bits(t_md5 *md5, t_ssl *ssl, char *input);
void	md5_algo(t_md5 *md5, int i);
char	*md5_out(t_md5 *md5);

/*
** SHA-256 Functions
*/

char	*sha256_exe(t_ssl *ssl, char *input);
void	sha256_init(t_sha *sha);
void	sha256_init1(t_sha *sha);
void	sha256_init2(t_sha *sha);
void	sha256_bits(t_sha *sha, t_ssl *ssl, char *input);
void	sha256_words(t_sha *sha, size_t *j);
void	sha256_var_init(t_sha *sha);
void	sha256_algo(t_sha *sha);
void	sha256_add_chunk(t_sha *sha);
char	*sha256_out(t_sha *sha);


#endif