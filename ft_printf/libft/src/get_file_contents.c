/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_contents.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 02:05:44 by jmeier            #+#    #+#             */
/*   Updated: 2018/09/01 12:28:45 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

static size_t	lines(int fd, char **fill)
{
	if (fd != -1)
		close(fd);
	*fill = NULL;
	return (0);
}

size_t			get_file_contents(char *filename, char **fill)
{
	char	buf[1024];
	size_t	ret;
	int		fd;
	int		i;

	if (!filename || !fill)
		return (0);
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	if (!(*fill = ft_strnew(0)))
		return (lines(fd, fill));
	ret = 0;
	while ((i = read(fd, buf, 1023)))
	{
		if (i == -1)
			return (lines(fd, fill));
		buf[i] = '\0';
		if (!(*fill = ft_realloc(*fill, ret + i)))
			return (lines(fd, fill));
		ft_memcpy(&(*fill)[ret], buf, i);
		ret += i;
	}
	close(fd);
	return (ret);
}
