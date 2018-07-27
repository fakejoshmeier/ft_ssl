/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 22:26:46 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/27 03:37:32 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int		read_commands(char **av, t_ssl *ssl)
{
	if (ft_strequ(*av, "md5"))
	{
		ssl->cmd = message_digest;
		ssl->exe = md5_exe;
		primer(ssl, "MD5", "md5", MESSAGE_DIGEST_FLAGS);
	}
	else if (ft_strequ(*av, "sha256"))
	{
		ssl->cmd = message_digest;
		ssl->exe = sha256_exe;
		primer(ssl, "SHA256", "sha256", MESSAGE_DIGEST_FLAGS);
	}
	// else if (ft_strequ(*av, "sha512"))
	// {
	// 	ssl->cmd = message_digest;
	// 	ssl->exe = sha256_exe;
	// 	primer(ssl, "SHA512", "sha512", MESSAGE_DIGEST_FLAGS);	
	// }
	return (ssl->exe ? 1 : 0);
}

void	primer(t_ssl *ssl, char *op, char *op_, char *flags)
{
	char	_cmd[ft_strlen(op) + 1];
	char	cmd_[ft_strlen(op_) + 1];
	char	flag[ft_strlen(flags) + 1];

	ft_strcpy(_cmd, op);
	ssl->_cmd = _cmd;
	ft_strcpy(cmd_, op_);
	ssl->cmd_ = cmd_;
	ft_strcpy(flags, flag);
	ssl->valid_flags = flag;
}
