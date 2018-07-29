/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 02:10:50 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/28 18:49:16 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	sha512_init(t_s512 *sha)
{
	sha->h0 = 0x6a09e667f3bcc908;
	sha->h1 = 0xbb67ae8584caa73b;
	sha->h2 = 0x3c6ef372fe94f82b;
	sha->h3 = 0xa54ff53a5f1d36f1;
	sha->h4 = 0x510e527fade682d1;
	sha->h5 = 0x9b05688c2b3e6c1f;
	sha->h6 = 0x1f83d9abfb41bd6b;
	sha->h7 = 0x5be0cd19137e2179;
	sha512_init1(sha);
	sha512_init2(sha);
	sha512_init3(sha);
	sha512_init4(sha);
}

void	sha512_init1(t_s512 *sha)
{
	sha->k[0] = 0x428a2f98d728ae22;
	sha->k[1] = 0x7137449123ef65cd;
	sha->k[2] = 0xb5c0fbcfec4d3b2f;
	sha->k[3] = 0xe9b5dba58189dbbc;
	sha->k[4] = 0x3956c25bf348b538;
	sha->k[5] = 0x59f111f1b605d019;
	sha->k[6] = 0x923f82a4af194f9b;
	sha->k[7] = 0xab1c5ed5da6d8118;
	sha->k[8] = 0xd807aa98a3030242;
	sha->k[9] = 0x12835b0145706fbe;
	sha->k[10] = 0x243185be4ee4b28c;
	sha->k[11] = 0x550c7dc3d5ffb4e2;
	sha->k[12] = 0x72be5d74f27b896f;
	sha->k[13] = 0x80deb1fe3b1696b1;
	sha->k[14] = 0x9bdc06a725c71235;
	sha->k[15] = 0xc19bf174cf692694;
	sha->k[16] = 0xe49b69c19ef14ad2;
	sha->k[17] = 0xefbe4786384f25e3;
	sha->k[18] = 0x0fc19dc68b8cd5b5;
	sha->k[19] = 0x240ca1cc77ac9c65;
	sha->k[20] = 0x2de92c6f592b0275;
	sha->k[21] = 0x4a7484aa6ea6e483;
	sha->k[22] = 0x5cb0a9dcbd41fbd4;
	sha->k[23] = 0x76f988da831153b5;
	sha->k[24] = 0x983e5152ee66dfab;
}

void	sha512_init2(t_s512 *sha)
{
	sha->k[25] = 0xa831c66d2db43210;
	sha->k[26] = 0xb00327c898fb213f;
	sha->k[27] = 0xbf597fc7beef0ee4;
	sha->k[28] = 0xc6e00bf33da88fc2;
	sha->k[29] = 0xd5a79147930aa725;
	sha->k[30] = 0x06ca6351e003826f;
	sha->k[31] = 0x142929670a0e6e70;
	sha->k[32] = 0x27b70a8546d22ffc;
	sha->k[33] = 0x2e1b21385c26c926;
	sha->k[34] = 0x4d2c6dfc5ac42aed;
	sha->k[35] = 0x53380d139d95b3df;
	sha->k[36] = 0x650a73548baf63de;
	sha->k[37] = 0x766a0abb3c77b2a8;
	sha->k[38] = 0x81c2c92e47edaee6;
	sha->k[39] = 0x92722c851482353b;
	sha->k[40] = 0xa2bfe8a14cf10364;
	sha->k[41] = 0xa81a664bbc423001;
	sha->k[42] = 0xc24b8b70d0f89791;
	sha->k[43] = 0xc76c51a30654be30;
	sha->k[44] = 0xd192e819d6ef5218;
	sha->k[45] = 0xd69906245565a910;
	sha->k[46] = 0xf40e35855771202a;
	sha->k[47] = 0x106aa07032bbd1b8;
	sha->k[48] = 0x19a4c116b8d2d0c8;
	sha->k[49] = 0x1e376c085141ab53;
}

void	sha512_init3(t_s512 *sha)
{
	sha->k[50] = 0x2748774cdf8eeb99;
	sha->k[51] = 0x34b0bcb5e19b48a8;
	sha->k[52] = 0x391c0cb3c5c95a63;
	sha->k[53] = 0x4ed8aa4ae3418acb;
	sha->k[54] = 0x5b9cca4f7763e373;
	sha->k[55] = 0x682e6ff3d6b2b8a3;
	sha->k[56] = 0x748f82ee5defb2fc;
	sha->k[57] = 0x78a5636f43172f60;
	sha->k[58] = 0x84c87814a1f0ab72;
	sha->k[59] = 0x8cc702081a6439ec;
	sha->k[60] = 0x90befffa23631e28;
	sha->k[61] = 0xa4506cebde82bde9;
	sha->k[62] = 0xbef9a3f7b2c67915;
	sha->k[63] = 0xc67178f2e372532b;
	sha->k[64] = 0xca273eceea26619c;
	sha->k[65] = 0xd186b8c721c0c207;
	sha->k[66] = 0xeada7dd6cde0eb1e;
	sha->k[67] = 0xf57d4f7fee6ed178;
	sha->k[68] = 0x06f067aa72176fba;
	sha->k[69] = 0x0a637dc5a2c898a6;
	sha->k[70] = 0x113f9804bef90dae;
	sha->k[71] = 0x1b710b35131c471b;
	sha->k[72] = 0x28db77f523047d84;
	sha->k[73] = 0x32caab7b40c72493;
	sha->k[74] = 0x3c9ebe0a15c9bebc;
}

void	sha512_init4(t_s512 *sha)
{
	sha->k[75] = 0x431d67c49c100d4c;
	sha->k[76] = 0x4cc5d4becb3e42b6;
	sha->k[77] = 0x597f299cfc657e2a;
	sha->k[78] = 0x5fcb6fab3ad6faec;
	sha->k[79] = 0x6c44198c4a475817;
}
