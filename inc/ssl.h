/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:37:10 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/22 18:39:13 by jmeier           ###   ########.fr       */
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
# define MESSAGE_DIGEST_FLAGS "-p -q -r -s"
# define BASE64_FLAGS "-d -e -i -o"
# define DES_FLAGS "-a -d -e -i -k -o -p -s -v"
# define B64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
# define MD5_F1(b, c, d) ((b & c) | ((~b) & d))
# define MD5_F2(b, c, d) ((d & b) | ((~d) & c))
# define MD5_F3(b, c, d) (b ^ c ^ d)
# define MD5_F4(b, c, d) (c ^ (b | (~d)))
# define LEFT_ROT(x, c) ((x << c) | (x >> (32 - c)))
# define RITE_ROT(x, c) ((x >> c) | (x << (32 - c)))
# define S512_ROT(x, c) ((x >> c) | (x << (64 - c)))

typedef union		u_bit64
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

typedef struct		s_b64
{
	int				yon;
	int				san;
	int				out_a;
	int				out_b;
	int				out_c;
	int				out_d;
	int				out_e;
}					t_b64;

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

typedef struct		s_s512
{
	uint64_t		h0;
	uint64_t		h1;
	uint64_t		h2;
	uint64_t		h3;
	uint64_t		h4;
	uint64_t		h5;
	uint64_t		h6;
	uint64_t		h7;
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
	uint64_t		t1;
	uint64_t		t2;
	uint64_t		k[80];
	uint64_t		w[80];
	uint8_t			*msg;
}					t_s512;

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
	unsigned int	a;
	unsigned int	d;
	unsigned int	e;
	unsigned int	i;
	unsigned int	k;
	unsigned int	o;
	unsigned int	p;
	unsigned int	q;
	unsigned int	r;
	unsigned int	s;
	unsigned int	v;
}					t_flag;

typedef struct		s_ssl
{
	size_t			in_size;
	size_t			ou_size;
	char			*stdin_input;
	char			**file_in;
	char			*filename;
	int				file_tot;
	char			**str_in;
	char			*str_curr;
	int				str_tot;
	int				run;
	char			*cmd__;
	char			*cmd_;
	char			*valid_flags;
	t_flag			*flag;
	t_md5			*md5;
	void			(*cmd)(struct s_ssl *);
	char			*(*exe)(struct s_ssl *, char *);
}					t_ssl;

/*
** Main and Error handling
*/

int					main(int ac, char *av[]);
void				ft_error(char *str, int i);
t_flag				*read_flags(char ***av, char *valid, t_ssl *ssl);

/*
** I/O handling
*/

int					read_commands(char **av, t_ssl *ssl);
int					read_commands1(char **av, t_ssl *ssl);
int					read_commands2(char **av, t_ssl *ssl);
void				primer(t_ssl *ssl, char *op, char *op_, char *valid);
void				message_digest(t_ssl *ssl);
void				message_digest_print(t_ssl *ssl, char *in, int id);
void				message_digest_str(t_ssl *ssl);
void				message_digest_file(t_ssl *ssl);
char				*stdin_in(t_ssl *ssl);
char				*file_in(t_ssl *ssl);
void				std_out(t_ssl *ssl, char *in, char *out);
void				str_out(t_ssl *ssl, char *in, char *out);
void				file_out(t_ssl *ssl, char *out);

/*
** Endian functions
*/

uint64_t			b_endian64(uint64_t num);
uint32_t			b_endian32(uint32_t num);
int					check_endianness(void);

/*
** MD5 Functions
*/

char				*md5_exe(t_ssl *ssl, char *input);
void				md5_init(t_md5 *md, int i);
void				md5_init2(t_md5 *md, int i);
void				md5_hex(t_md5 *md5);
void				md5_hex1(t_md5 *md5);
void				md5_hex2(t_md5 *md5);
void				md5_bits(t_md5 *md5, t_ssl *ssl, char *input);
void				md5_algo(t_md5 *md5, int i);
char				*md5_out(t_md5 *md5);

/*
** SHA-224 Functions - Uses most of the SHA-256 functions
*/

char				*sha224_exe(t_ssl *ssl, char *input);
void				sha224_init(t_sha *sha);
char				*sha224_out(t_sha *sha);

/*
** SHA-256 Functions
*/

char				*sha256_exe(t_ssl *ssl, char *input);
void				sha256_init(t_sha *sha);
void				sha256_init1(t_sha *sha);
void				sha256_init2(t_sha *sha);
void				sha256_bits(t_sha *sha, t_ssl *ssl, char *input);
void				sha256_words(t_sha *sha, uint8_t *msg);
void				sha256_round(t_sha *sha);
void				sha256_algo(t_sha *sha);
char				*sha256_out(t_sha *sha);

/*
** SHA-384 Functions - Uses most of the SHA-512 functions
*/

char				*sha384_exe(t_ssl *ssl, char *input);
void				sha384_init(t_s512 *sha);
char				*sha384_out(t_s512 *sha);

/*
** SHA-512 Functions
*/

char				*sha512_exe(t_ssl *ssl, char *in);
void				sha512_init(t_s512 *sha);
void				sha512_init1(t_s512 *sha);
void				sha512_init2(t_s512 *sha);
void				sha512_init3(t_s512 *sha);
void				sha512_init4(t_s512 *sha);
void				sha512_bits(t_s512 *sha, t_ssl *ssl, char *input);
void				sha512_words(t_s512 *sha, uint8_t *msg);
void				sha512_round(t_s512 *sha);
void				sha512_algo(t_s512 *sha);
char				*sha512_out(t_s512 *sha);

/*
** Base64 functions
*/

char				*base64_exe(t_ssl *ssl, char *in);
void				base64_encode(char *in, int len, char *ret, int ret_len);
char				*base64_decode(char *in, int len, int ret_len);
char				*newline_trim(char *in, int *len);
int					*decrypt_ref_table(void);

#endif
