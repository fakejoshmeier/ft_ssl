/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 22:26:46 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/27 02:43:21 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int		read_commands(char **av, t_ssl *ssl)
{
	if (ft_strequ(*av, "md5"))
	{
		primer(ssl, "MD5", "md5");
		strike(ssl, message_digest, md5_exe, md_flags);
	}
	else if (ft_strequ(*av, "sha224"))
	{
		primer(ssl, "SHA224", "sha224");
		strike(ssl, message_digest, sha224_exe, md_flags);
	}
	else if (ft_strequ(*av, "sha256"))
	{
		primer(ssl, "SHA256", "sha256");
		strike(ssl, message_digest, sha256_exe, md_flags);
	}
	else if (ft_strequ(*av, "sha384"))
	{
		primer(ssl, "SHA384", "sha384");
		strike(ssl, message_digest, sha384_exe, md_flags);
	}
	return (ssl->exe ? 1 : read_commands1(av, ssl));
}

int		read_commands1(char **av, t_ssl *ssl)
{
	if (ft_strequ(*av, "sha512"))
	{
		primer(ssl, "SHA512", "sha512");
		strike(ssl, message_digest, sha512_exe, md_flags);
	}
	else if (ft_strequ(*av, "base64"))
		strike(ssl, cipher, base64_exe, b64_flags);
	else if (ft_strequ(*av, "des"))
		strike(ssl, cipher, ecb_exe, ecb_flags);
	else if (ft_strequ(*av, "des-ecb"))
		strike(ssl, cipher, ecb_exe, ecb_flags);
	else if (ft_strequ(*av, "des-cbc"))
		strike(ssl, cipher, cbc_exe, cbc_flags);
	else if (ft_strequ(*av, "des3-ecb"))
		strike(ssl, cipher, ecb3_exe, ecb3_flags);
	else if (ft_strequ(*av, "des3-cbc"))
		strike(ssl, cipher, cbc3_exe, cbc3_flags);
	return (ssl->exe ? 1 : 0);
}

void	primer(t_ssl *ssl, char *op, char *op_)
{
	ssl->cmd__ = op;
	ssl->cmd_ = op_;
}

void	strike(t_ssl *ssl, void (*c)(t_ssl *), char *(*e)(t_ssl *, char *),
		t_flag *(*f)(char ***, t_ssl *))
{
	ssl->cmd = c;
	ssl->exe = e;
	ssl->fla = f;
}
