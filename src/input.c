/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:53:38 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/25 04:26:41 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int		read_commands(char **av, t_ssl *ssl)
{
	if (ft_strequ(*av, "md5"))
	{
		ssl->cmd = message_digest;
		ssl->exe = md5_exe;
		primer(ssl, "MD5", "md5");
	}
	else if (ft_strequ(*av, "sha256"))
	{
		ssl->cmd = message_digest;
		ssl->exe = sha256_exe;
		primer(ssl, "SHA256", "sha256");
	}
	return (ssl->exe ? 1 : 0);
}

void	primer(t_ssl *ssl, char *op, char *op_)
{
	char	cmd[ft_strlen(op) + 1];
	char	cmd_[ft_strlen(op_) + 1];

	ft_strcpy(cmd, op);
	ssl->cmd = cmd;
	ft_strcpy(cmd_, op_);
	ssl->cmd_ = cmd_;
}

void	read_inputs(char **av, t_ssl *ssl)
{

}