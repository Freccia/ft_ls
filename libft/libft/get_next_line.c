/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:53:42 by lfabbro           #+#    #+#             */
/*   Updated: 2016/02/22 16:26:44 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int				ft_end_of_line(t_save **save)
{
	long				i;

	i = 0;
	while ((*save)->ptr[i] != '\n' && (*save)->ptr[i] != '\0')
		++i;
	(*save)->line_len = i;
	if ((*save)->ptr[i] == '\n')
		return (((*save)->ptr - (*save)->buf) + i <= (*save)->buf_len);
	return (0);
}

static int				ft_increase_buf(t_save **save)
{
	long				ptr_pos;
	char				*new_buf;
	long				new_size;

	ptr_pos = (*save)->ptr - (*save)->buf;
	new_size = (*save)->buf_size * I_SIZE;
	if ((new_buf = ft_strnew(new_size)) == NULL)
		return (1);
	ft_strcpy(new_buf, (*save)->buf);
	free((*save)->buf);
	(*save)->buf = new_buf;
	(*save)->buf_size = new_size;
	(*save)->ptr = (*save)->buf + ptr_pos;
	return (0);
}

static int				ft_init_save(t_save **save)
{
	if ((*save = malloc(sizeof(t_save))) == NULL)
		return (1);
	if (((*save)->buf = ft_strnew(BUFF_SIZE)) == NULL)
		return (1);
	(*save)->ret = 1;
	(*save)->buf_size = BUFF_SIZE;
	(*save)->buf_len = 0;
	(*save)->line_len = 0;
	(*save)->ptr = (*save)->buf;
	return (0);
}

static int				ft_return(t_save **ptr_save, t_save *save, char **line)
{
	long				test;

	test = ((save->ptr - save->buf) + save->line_len);
	if (save->ret < 0)
		return (-1);
	if ((*line = ft_strnew(save->line_len)) == NULL)
		return (-1);
	ft_strncpy(*line, save->ptr, save->line_len);
	save->ptr += save->line_len + 1;
	if (test >= save->buf_len && !save->line_len && !save->ret)
	{
		if (save->buf != NULL)
			free(save->buf);
		free(save);
		*ptr_save = NULL;
		return (0);
	}
	return (1);
}

int						get_next_line(int const fd, char **line)
{
	static t_save		*save[MAX_FD];

	if (fd < 0 || fd > MAX_FD || line == NULL)
		return (-1);
	if (!save[fd])
		if (ft_init_save(&save[fd]))
			return (-1);
	while (!ft_end_of_line(&save[fd]) && save[fd]->ret > 0)
	{
		while (save[fd]->buf_size < save[fd]->buf_len + BUFF_SIZE)
			if (ft_increase_buf(&save[fd]))
				return (-1);
		save[fd]->ret = read(fd, save[fd]->buf + save[fd]->buf_len, BUFF_SIZE);
		save[fd]->buf_len += save[fd]->ret;
	}
	return (ft_return(&save[fd], save[fd], line));
}
