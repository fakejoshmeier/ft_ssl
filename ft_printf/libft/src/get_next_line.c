/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 09:34:13 by jmeier            #+#    #+#             */
/*   Updated: 2018/07/08 22:58:06 by jmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		parse(t_block **block, char **line)
{
	int		i;

	i = 0;
	while ((*block)->str[i] && (*block)->str[i] != '\n')
		i++;
	if ((*block)->str[i] == '\n')
	{
		ASSERT(*line = ft_strsub((*block)->str, 0, i));
		ASSERT((*block)->tmp = ft_strdup((*block)->str + i + 1));
		free((*block)->str);
		(*block)->str = (*block)->tmp;
	}
	else if (!(*block)->str[i])
	{
		if (i == 0)
			return (0);
		ASSERT(*line = ft_strdup((*block)->str));
		free((*block)->str);
		(*block)->str = NULL;
	}
	return (1);
}

static t_block	*cycle_fd(t_block **train, const int fd)
{
	t_block			*tmp;

	tmp = *train;
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	if (!tmp)
	{
		NULL_GUARD(tmp = (t_block *)ft_memalloc(sizeof(t_block)));
		tmp->fd = fd;
		NULL_GUARD(tmp->str = ft_strnew(0));
		tmp->next = *train;
		*train = tmp;
	}
	return (tmp);
}

int				get_next_line(const int fd, char **line)
{
	static t_block	*train;
	t_block			*tmp;
	char			buf[BUFF_SIZE + 1];

	ASSERT(fd >= 0 || line);
	tmp = cycle_fd(&train, fd);
	while ((tmp->len = read(tmp->fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[tmp->len] = '\0';
		ASSERT(tmp->str);
		ASSERT(tmp->tmp = ft_strjoin(tmp->str, buf));
		free(tmp->str);
		ASSERT(tmp->str = ft_strdup(tmp->tmp));
		free(tmp->tmp);
		tmp->tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	ASSERT(tmp->len >= 0);
	if (!tmp->len && !tmp->str)
	{
		tmp->fd = 0;
		return (0);
	}
	return (parse(&tmp, line));
}
