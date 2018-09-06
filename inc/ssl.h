/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 16:37:10 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/06 13:38:56 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H
# include "ssl_macros.h"
# include <libft.h>
# include <ft_printf.h>
# include <limits.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <readpassphrase.h>

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
	int				iter;
	int				out_a;
	int				out_b;
	int				out_c;
	int				out_d;
	int				out_e;
}					t_b64;

typedef struct		s_des
{
	uint64_t		nacl;
	uint64_t		key;
	uint32_t		l[16];
	uint32_t		r[16];
	uint64_t		subkey[16];
	uint64_t		init_perm_ret;
	char			*user_key;
	char			*user_iv;
	int				*pc1;
	int				*pc2;
	int				*shifts;
	int				*init_perm;
	int				*ebit;
	int				*s[8][4];
	int				*p32;
	int				*final_perm;
}					t_des;

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
	char			*user_pass;
	char			*user_salt;
	char			*user_key;
	char			*user_iv;
	char			*stdin_input;
	char			**file_in;
	char			*filename;
	char			*ou_file;
	int				file_tot;
	char			**str_in;
	char			*str_curr;
	int				str_tot;
	int				run;
	char			*cmd__;
	char			*cmd_;
	t_flag			*flag;
	t_md5			*md5;
	void			(*cmd)(struct s_ssl *);
	char			*(*exe)(struct s_ssl *, char *);
	t_flag			*(*fla)(char ***, struct s_ssl *);
}					t_ssl;

/*
** Main and Error handling
*/

int					main(int ac, char *av[]);
void				ft_error(char *str, int i);

/*
** I/O handling
*/

int					read_commands(char **av, t_ssl *ssl);
int					read_commands1(char **av, t_ssl *ssl);
int					read_commands2(char **av, t_ssl *ssl);
void				primer(t_ssl *ssl, char *op, char *op_);
void				strike(t_ssl *ssl, void (*c)(t_ssl *),
					char *(*e)(t_ssl *, char *),
					t_flag *(*f)(char ***, t_ssl *));
void				message_digest(t_ssl *ssl);
void				message_digest_print(t_ssl *ssl, char *in, int id);
void				message_digest_str(t_ssl *ssl);
void				message_digest_file(t_ssl *ssl);
void				cipher(t_ssl *ssl);
int					write_to_file(char *out, char *file, size_t len);
char				*stdin_in(t_ssl *ssl);
char				*file_in(t_ssl *ssl);
void				std_out(t_ssl *ssl, char *in, char *out);
void				str_out(t_ssl *ssl, char *in, char *out);
void				file_out(t_ssl *ssl, char *out);

/*
** Flag handling
*/

t_flag				*md_flags(char ***av, t_ssl *ssl);
t_flag				*b64_flags(char ***av, t_ssl *ssl);
t_flag				*ecb_flags(char ***av, t_ssl *ssl);
t_flag				*cbc_flags(char ***av, t_ssl *ssl);

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
** Base64 Functions
*/

char				*base64_exe(t_ssl *ssl, char *in);
void				base64_encode(char *in, int len, char *ret, int ret_len);
char				*base64_decode(char *in, int len, int ret_len);
char				*whitespace_trim(char *in, size_t *len);
int					*decrypt_ref_table(void);

/*
** DES Functions
*/

void				des_init(t_des *des);
void				des_pbkdf(t_ssl *ssl, t_des *des, char **in);
void				des_subkeys(t_des *des, unsigned int r);
uint64_t			permute_key_by_x_for_y(uint64_t key, int *pc, int size);
char				*des_enc_out(t_ssl *ssl, t_des *des);
uint64_t			process_msg(t_des *Des, uint64_t);
uint32_t			des_f(t_des *des, uint32_t blk, uint64_t key);
void				des_clean(t_ssl *ssl, t_des *des);
char				*a(char *pass, uint64_t salt);
char				*str_to_hex(char *s);
char				*rand_hex_str(int size);
char				convert_hex_char_to_4bit(uint8_t c);
uint64_t			extract_salt(t_ssl *ssl, char **in);
uint64_t			hex_str_to_64bit(char *s);
uint64_t			des_str_to_64bit(char **in, size_t *len);
uint64_t			blender(char *key);

/*
** ECB Functions
*/

char				*ecb_exe(t_ssl *ssl, char *in);
char				*ecb_encrypt(t_des *des, t_ssl *ssl, char *in);
char				*ecb_decrypt(t_des *des, t_ssl *ssl, char *in);

/*
** CBC Functions
*/

char				*cbc_exe(t_ssl *ssl, char *in);
char				*cbc_encrypt(t_des *des, t_ssl *ssl, char *in);
char				*cbc_decrypt(t_des *des, t_ssl *ssl, char *in);

#endif
