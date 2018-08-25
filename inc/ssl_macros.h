/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_macros.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 23:31:51 by jmeier            #+#    #+#             */
/*   Updated: 2018/08/25 07:44:36 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SSL_MACROS_H
# define SSL_MACROS_H

# define USAGE "usage: ft_ssl command [command opts] [command args]"

# define B64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

# define PC1_A "57 49 41 33 25 17 9 1 58 50 42 34 26 18 "
# define PC1_B "10 2 59 51 43 35 27 19 11 3 60 52 44 36 "
# define PC1_C "63 55 47 39 31 23 15 7 62 54 46 38 30 22 "
# define PC1_D "14 6 61 53 45 37 29 21 13 5 28 20 12 4"
# define PC1 PC1_A PC1_B PC1_C PC1_D

# define PC2_A "14 17 11 24 1 5 3 28 15 6 21 10 "
# define PC2_B "23 19 12 4 26 8 16 7 27 20 13 2 "
# define PC2_C "41 52 31 37 47 55 30 40 51 45 33 48 "
# define PC2_D "44 49 39 56 34 53 46 42 50 36 29 32"
# define PC2 PC2_A PC2_B PC2_C PC2_D

# define SHIFT_BY "1 1 2 2 2 2 2 2 1 2 2 2 2 2 2 1"

# define IP_A "58 50 42 34 26 18 10 2 60 52 44 36 28 20 12 4 "
# define IP_B "62 54 46 38 30 22 14 6 64 56 48 40 32 24 16 8 "
# define IP_C "57 49 41 33 25 17 9 1 59 51 43 35 27 19 11 3 "
# define IP_D "61 53 45 37 29 21 13 5 63 55 47 39 31 23 15 7"
# define IP IP_A IP_B IP_C IP_D

# define EBIT_A "32 1 2 3 4 5 4 5 6 7 8 9 8 9 10 11 12 13 12 13 14 15 16 17 16 "
# define EBIT_B "17 18 19 20 21 20 21 22 23 24 25 24 25 26 27 28 29 28 29 30 "
# define EBIT_C "31 32 1"
# define EBIT EBIT_A EBIT_B EBIT_C
# define S1_A "14 4 13 1 2 15 11 8 3 10 6 12 5 9 0 7"
# define S1_B "0 15 7 4 14 2 13 1 10 6 12 11 9 5 3 8"
# define S1_C "4 1 14 8 13 6 2 11 15 12 9 7 3 10 5 0"
# define S1_D "15 12 8 2 4 9 1 7 5 11 3 14 10 0 6 13"
# define GET_S1_A des->s[0][0] = ft_atoi_arr(S1_A);
# define GET_S1_B des->s[0][1] = ft_atoi_arr(S1_B);
# define GET_S1_C des->s[0][2] = ft_atoi_arr(S1_C);
# define GET_S1_D des->s[0][3] = ft_atoi_arr(S1_D)
# define GET_S1 GET_S1_A GET_S1_B GET_S1_C GET_S1_D

# define S2_A "15 1 8 14 6 11 3 4 9 7 2 13 12 0 5 10"
# define S2_B "3 13 4 7 15 2 8 14 12 0 1 10 6 9 11 5"
# define S2_C "0 14 7 11 10 4 13 1 5 8 12 6 9 3 2 15"
# define S2_D "13 8 10 1 3 15 4 2 11 6 7 12 0 5 14 9"
# define GET_S2_A des->s[1][0] = ft_atoi_arr(S2_A);
# define GET_S2_B des->s[1][1] = ft_atoi_arr(S2_B);
# define GET_S2_C des->s[1][2] = ft_atoi_arr(S2_C);
# define GET_S2_D des->s[1][3] = ft_atoi_arr(S2_D)
# define GET_S2 GET_S2_A GET_S2_B GET_S2_C GET_S2_D

# define S3_A "10 0 9 14 6 3 15 5 1 13 12 7 11 4 2 8"
# define S3_B "13 7 0 9 3 4 6 10 2 8 5 14 12 11 15 1"
# define S3_C "13 6 4 9 8 15 3 0 11 1 2 12 5 10 14 7"
# define S3_D "1 10 13 0 6 9 8 7 4 15 14 3 11 5 2 12"
# define GET_S3_A des->s[2][0] = ft_atoi_arr(S3_A);
# define GET_S3_B des->s[2][1] = ft_atoi_arr(S3_B);
# define GET_S3_C des->s[2][2] = ft_atoi_arr(S3_C);
# define GET_S3_D des->s[2][3] = ft_atoi_arr(S3_D)
# define GET_S3 GET_S3_A GET_S3_B GET_S3_C GET_S3_D

# define S4_A "7 13 14 3 0 6 9 10 1 2 8 5 11 12 4 15"
# define S4_B "13 8 11 5 6 15 0 3 4 7 2 12 1 10 14 9"
# define S4_C "10 6 9 0 12 11 7 13 15 1 3 14 5 2 8 4"
# define S4_D "3 15 0 6 10 1 13 8 9 4 5 11 12 7 2 14"
# define GET_S4_A des->s[3][0] = ft_atoi_arr(S4_A);
# define GET_S4_B des->s[3][1] = ft_atoi_arr(S4_B);
# define GET_S4_C des->s[3][2] = ft_atoi_arr(S4_C);
# define GET_S4_D des->s[3][3] = ft_atoi_arr(S4_D)
# define GET_S4 GET_S4_A GET_S4_B GET_S4_C GET_S4_D

# define S5_A "2 12 4 1 7 10 11 6 8 5 3 15 13 0 14 9"
# define S5_B "14 11 2 12 4 7 13 1 5 0 15 10 3 9 8 6"
# define S5_C "4 2 1 11 10 13 7 8 15 9 12 5 6 3 0 14"
# define S5_D "11 8 12 7 1 14 2 13 6 15 0 9 10 4 5 3"
# define GET_S5_A des->s[4][0] = ft_atoi_arr(S5_A);
# define GET_S5_B des->s[4][1] = ft_atoi_arr(S5_B);
# define GET_S5_C des->s[4][2] = ft_atoi_arr(S5_C);
# define GET_S5_D des->s[4][3] = ft_atoi_arr(S5_D)
# define GET_S5 GET_S5_A GET_S5_B GET_S5_C GET_S5_D

# define S6_A "12 1 10 15 9 2 6 8 0 13 3 4 14 7 5 11"
# define S6_B "10 15 4 2 7 12 9 5 6 1 13 14 0 11 3 8"
# define S6_C "9 14 15 5 2 8 12 3 7 0 4 10 1 13 11 6"
# define S6_D "4 3 2 12 9 5 15 10 11 14 1 7 6 0 8 13"
# define GET_S6_A des->s[5][0] = ft_atoi_arr(S6_A);
# define GET_S6_B des->s[5][1] = ft_atoi_arr(S6_B);
# define GET_S6_C des->s[5][2] = ft_atoi_arr(S6_C);
# define GET_S6_D des->s[5][3] = ft_atoi_arr(S6_D)
# define GET_S6 GET_S6_A GET_S6_B GET_S6_C GET_S6_D

# define S7_A "4 11 2 14 15 0 8 13 3 12 9 7 5 10 6 1"
# define S7_B "13 0 11 7 4 9 1 10 14 3 5 12 2 15 8 6"
# define S7_C "1 4 11 13 12 3 7 14 10 15 6 8 0 5 9 2"
# define S7_D "6 11 13 8 1 4 10 7 9 5 0 15 14 2 3 12"
# define GET_S7_A des->s[6][0] = ft_atoi_arr(S7_A);
# define GET_S7_B des->s[6][1] = ft_atoi_arr(S7_B);
# define GET_S7_C des->s[6][2] = ft_atoi_arr(S7_C);
# define GET_S7_D des->s[6][3] = ft_atoi_arr(S7_D)
# define GET_S7 GET_S7_A GET_S7_B GET_S7_C GET_S7_D

# define S8_A "13 2 8 4 6 15 11 1 10 9 3 14 5 0 12 7"
# define S8_B "1 15 13 8 10 3 7 4 12 5 6 11 0 14 9 2"
# define S8_C "7 11 4 1 9 12 14 2 0 6 10 13 15 3 5 8"
# define S8_D "2 1 14 7 4 10 8 13 15 12 9 0 3 5 6 11"
# define GET_S8_A des->s[7][0] = ft_atoi_arr(S8_A);
# define GET_S8_B des->s[7][1] = ft_atoi_arr(S8_B);
# define GET_S8_C des->s[7][2] = ft_atoi_arr(S8_C);
# define GET_S8_D des->s[7][3] = ft_atoi_arr(S8_D)
# define GET_S8 GET_S8_A GET_S8_B GET_S8_C GET_S8_D

# define P_A "16 7 20 21 29 12 28 17 1 15 23 26 5 18 31 10 2 8 24 14 "
# define P_B "32 27 3 9 19 13 30 6 22 11 4 25"
# define P_TABLE P_A P_B

# define MD5_F1(b, c, d) ((b & c) | ((~b) & d))
# define MD5_F2(b, c, d) ((d & b) | ((~d) & c))
# define MD5_F3(b, c, d) (b ^ c ^ d)
# define MD5_F4(b, c, d) (c ^ (b | (~d)))

# define LEFT_ROT(x, c) ((x << c) | (x >> (32 - c)))
# define RITE_ROT(x, c) ((x >> c) | (x << (32 - c)))
# define S512_ROT(x, c) ((x >> c) | (x << (64 - c)))
# define DES_ROT(a, b) (((a << b) | (a >> (28 - b))) & 0xFFFFFFF)

#endif
