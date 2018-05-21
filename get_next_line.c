/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:01:42 by sgarcia           #+#    #+#             */
/*   Updated: 2018/05/21 18:15:25 by sgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		verif_line(int fd, char **line, char **copy, t_read r)
{
	if (r.i != -2)
		ft_strdel(&copy[fd]);
	if (r.i == -1)
		return (-1);
	else
	{
		if (r.i > 0 && first_occ(*line, '\n') != -1)
			copy[fd] = strdup_free(r.buf[fd]);
		if ((r.i == -2 || r.i > 0) && first_occ(*line, '\n') >= 0)
		{
			line[0][first_occ(*line, '\n')] = '\0';
			r.i = ft_strlen(ft_strchr(copy[fd], '\n') + 1) + 1;
			copy[fd] = ft_memcpy(copy[fd],
					(ft_strchr(copy[fd], '\n') + 1), r.i);
		}
		return (1);
	}
}

int				get_next_line(const int fd, char **line)
{
	static	char	*copy[OPEN_MAX];
	t_read			r;

	if (fd < 0 || fd > OPEN_MAX || BUFF_SIZE <= 0 || !line)
		return (-1);
	r.i = -2;
	r.buf[fd] = ft_strnew(BUFF_SIZE + 1);
	if (!copy[fd])
		copy[fd] = ft_strnew(BUFF_SIZE + 1);
	*line = ft_strdup(copy[fd]);
	while ((first_occ(*line, '\n') == -1) && (r.i == BUFF_SIZE || r.i == -2))
	{
		r.i = read(fd, r.buf[fd], BUFF_SIZE);
		if (r.i >= 0)
		{
			r.buf[fd][r.i] = '\0';
			*line = strjoin_free1(*line, r.buf[fd]);
		}
	}
	if (r.i != 0 ||
			(first_occ(*line, '\n') == -1 && first_occ(*line, '\0') > 0))
		return (verif_line(fd, &*line, &*copy, r));
	else
		return (0);
}
