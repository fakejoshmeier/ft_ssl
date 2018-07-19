/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 18:53:51 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/18 13:52:57 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	init_md5(t_md5 *md, int i)
{
	md->a = 0x67452301;
	md->b = 0xefcdab89;
	md->c = 0x98badcfe;
	md->d = 0x10325476;
	while (++i < 32)
	{
		if (i < 16)
		{
			MATCH(i % 4 == 0, md->s[i] = 7);
			MATCH(i % 4 == 1, md->s[i] = 12);
			MATCH(i % 4 == 2, md->s[i] = 17);
			MATCH(i % 4 == 3, md->s[i] = 22);
		}
		else if (16 <= i && i < 32)
		{
			MATCH(i % 4 == 0, md->s[i] = 5);
			OR(i % 4 == 1, md->s[i] = 9);
			OR(i % 4 == 2, md->s[i] = 14);
			OR(i % 4 == 3, md->s[i] = 20);
		}
	}
	fucking_norme(md, 31);
	md5_hex(md);
}

void	fucking_norme(t_md5 *md, int i)
{
	while (++i < 64)
	{
		if (32 <= i && i < 48)
		{
			MATCH(i % 4 == 0, md->s[i] = 4);
			OR(i % 4 == 1, md->s[i] = 11);
			OR(i % 4 == 2, md->s[i] = 16);
			OR(i % 4 == 3, md->s[i] = 23);
		}
		else if (48 <= i && i < 64)
		{
			MATCH(i % 4 == 0, md->s[i] = 6);
			OR(i % 4 == 1, md->s[i] = 10);
			OR(i % 4 == 2, md->s[i] = 15);
			OR(i % 4 == 3, md->s[i] = 21);
		}
	}
}

void	md5_hex(t_md5 *md5)
{
	md5->k[0] = 0xd76aa478;
	md5->k[1] = 0xe8c7b756;
	md5->k[2] = 0x242070db;
	md5->k[3] = 0xc1bdceee;
	md5->k[4] = 0xf57c0faf;
	md5->k[5] = 0x4787c62a;
	md5->k[6] = 0xa8304613;
	md5->k[7] = 0xfd469501;
	md5->k[8] = 0x698098d8;
	md5->k[9] = 0x8b44f7af;
	md5->k[10] = 0xffff5bb1;
	md5->k[11] = 0x895cd7be;
	md5->k[12] = 0x6b901122;
	md5->k[13] = 0xfd987193;
	md5->k[14] = 0xa679438e;
	md5->k[15] = 0x49b40821;
	md5->k[16] = 0xf61e2562;
	md5->k[17] = 0xc040b340;
	md5->k[18] = 0x265e5a51;
	md5->k[19] = 0xe9b6c7aa;
	md5->k[20] = 0xd62f105d;
	md5->k[21] = 0x02441453;
	md5->k[22] = 0xd8a1e681;
	md5->k[23] = 0xe7d3fbc8;
	md5_hex1(md5);
}

void	md5_hex1(t_md5 *md5)
{
	md5->k[24] = 0x21e1cde6;
	md5->k[25] = 0xc33707d6;
	md5->k[26] = 0xf4d50d87;
	md5->k[27] = 0x455a14ed;
	md5->k[28] = 0xa9e3e905;
	md5->k[29] = 0xfcefa3f8;
	md5->k[30] = 0x676f02d9;
	md5->k[31] = 0x8d2a4c8a;
	md5->k[32] = 0xfffa3942;
	md5->k[33] = 0x8771f681;
	md5->k[34] = 0x6d9d6122;
	md5->k[35] = 0xfde5380c;
	md5->k[36] = 0xa4beea44;
	md5->k[37] = 0x4bdecfa9;
	md5->k[38] = 0xf6bb4b60;
	md5->k[39] = 0xbebfbc70;
	md5->k[40] = 0x289b7ec6;
	md5->k[41] = 0xeaa127fa;
	md5->k[42] = 0xd4ef3085;
	md5->k[43] = 0x04881d05;
	md5->k[44] = 0xd9d4d039;
	md5->k[45] = 0xe6db99e5;
	md5->k[46] = 0x1fa27cf8;
	md5->k[47] = 0xc4ac5665;
	md5_hex2(md5);
}

void	md5_hex2(t_md5 *md5)
{
	md5->k[48] = 0xf4292244;
	md5->k[49] = 0x432aff97;
	md5->k[50] = 0xab9423a7;
	md5->k[51] = 0xfc93a039;
	md5->k[52] = 0x655b59c3;
	md5->k[53] = 0x8f0ccc92;
	md5->k[54] = 0xffeff47d;
	md5->k[55] = 0x85845dd1;
	md5->k[56] = 0x6fa87e4f;
	md5->k[57] = 0xfe2ce6e0;
	md5->k[58] = 0xa3014314;
	md5->k[59] = 0x4e0811a1;
	md5->k[60] = 0xf7537e82;
	md5->k[61] = 0xbd3af235;
	md5->k[62] = 0x2ad7d2bb;
	md5->k[63] = 0xeb86d391;
}