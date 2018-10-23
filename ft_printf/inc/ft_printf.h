/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:21:30 by jmeier            #+#    #+#             */
/*   Updated: 2018/05/22 03:55:14 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct	s_flags
{
	int			dash;
	int			zero;
	int			plus;
	int			hash;
	int			spess;
	int			width;
	int			prec;
	int			adr;
	int			wid_flag;
	int			prec_flag;
}				t_all;

int				ft_printf(const char *format, ...);
/*
** Parse functions
*/
void			parse_flags(va_list arg, int *i, const char *str, t_all *f);
void			parse_hflag(va_list arg, int *i, const char *str, t_all *f);
void			parse_hhflag(va_list arg, int *i, const char *str, t_all *f);
void			parse_lflag(va_list arg, int *i, const char *str, t_all *f);
void			parse_llflag(va_list arg, int *i, const char *str, t_all *f);
void			parse_zflag(va_list arg, int *i, const char *str, t_all *f);
void			parse_jflag(va_list arg, int *i, const char *str, t_all *f);
void			parse_escape(int *i, const char *str, t_all *f);
void			parse_width(const char *str, int *i, va_list arg, t_all *f);
void			parse_prec(const char *str, int *i, va_list arg, t_all *f);
void			parse_format(const char *str, int *i, t_all *f);
/*
** Casting couch ;)
*/
void			int_cast(va_list arg, t_all *f);
void			oct_cast(va_list arg, t_all *f);
void			hex_cast(va_list arg, t_all *f);
void			lhex_cast(va_list arg, t_all *f);
void			uint_cast(va_list arg, t_all *f);
void			h_int_cast(va_list arg, t_all *f);
void			h_oct_cast(va_list arg, t_all *f);
void			h_hex_cast(va_list arg, t_all *f);
void			h_lhex_cast(va_list arg, t_all *f);
void			h_uint_cast(va_list arg, t_all *f);
void			hh_int_cast(va_list arg, t_all *f);
void			hh_oct_cast(va_list arg, t_all *f);
void			hh_hex_cast(va_list arg, t_all *f);
void			hh_lhex_cast(va_list arg, t_all *f);
void			hh_uint_cast(va_list arg, t_all *f);
void			l_int_cast(va_list arg, t_all *f);
void			l_oct_cast(va_list arg, t_all *f);
void			l_hex_cast(va_list arg, t_all *f);
void			l_lhex_cast(va_list arg, t_all *f);
void			l_uint_cast(va_list arg, t_all *f);
void			ll_int_cast(va_list arg, t_all *f);
void			ll_oct_cast(va_list arg, t_all *f);
void			ll_hex_cast(va_list arg, t_all *f);
void			ll_lhex_cast(va_list arg, t_all *f);
void			ll_uint_cast(va_list arg, t_all *f);
void			j_int_cast(va_list arg, t_all *f);
void			j_oct_cast(va_list arg, t_all *f);
void			j_hex_cast(va_list arg, t_all *f);
void			j_lhex_cast(va_list arg, t_all *f);
void			j_uint_cast(va_list arg, t_all *f);
void			z_int_cast(va_list arg, t_all *f);
void			z_oct_cast(va_list arg, t_all *f);
void			z_hex_cast(va_list arg, t_all *f);
void			z_lhex_cast(va_list arg, t_all *f);
void			z_uint_cast(va_list arg, t_all *f);
void			char_cast(va_list arg, t_all *f);
void			str_cast(va_list arg, t_all *f);
void			elsie_cast(va_list arg, t_all *f);
void			loss_cast(va_list arg, t_all *f);
void			address(va_list arg, t_all *f);
void			ntame(va_list arg, t_all *f);
/*
** Precision and Width calculations and application
*/
void			putadr(unsigned long n, t_all *f);
void			char_prec(char output, t_all *f);
char			*char_width(char output, t_all *f);
char			*str_prec(char *output, t_all *f);
char			*str_width(char *output, t_all *f);
char			*prefix_parse(unsigned int outpu, int base, int caps, t_all *f);
char			*sign_prefix_parse(int output, t_all *f);
char			*sign_width_parse(long long output, t_all *f);
char			*width_parse(unsigned long long output, t_all *f, int base);
char			*prec_parse(unsigned long long output, t_all *f, int b);
char			*sign_prec_parse(long long output, t_all *f);
wchar_t			*ft_wstrncpy(wchar_t *dst, wchar_t *src, size_t n);
wchar_t			*wchar_prec(wchar_t *output, t_all *f);
char			*wchar_width(wchar_t *out, t_all *f);
wchar_t			*ft_wstrnew(int n);
void			pita(wchar_t *pita);
void			supa_free(char *s1, char *s2, char *s3);
void			percent(t_all *f);
int				ft_widelen(wchar_t *s);
int				isflag(char c);

#endif
