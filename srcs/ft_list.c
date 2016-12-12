/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:47:23 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:52:18 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_initpad(t_pad **pad)
{
	(*pad)->uid = 0;
	(*pad)->gid = 0;
	(*pad)->links = 0;
	(*pad)->bytes = 0;
	(*pad)->major = 0;
	(*pad)->minor = 0;
}

static void			ft_set_newdata(t_data **new, struct stat lbuf)
{
	(*new)->uid = NULL;
	(*new)->gid = NULL;
	(*new)->size = lbuf.st_size;
	(*new)->next = NULL;
}

t_data				*ft_newdata(char *name, char *dir, int opt)
{
	t_data			*new;
	char			*tmp;
	struct stat		lbuf;

	if ((new = (t_data*)malloc(sizeof(t_data))) == NULL)
		ft_perror("malloc");
	new->name = ft_strdup(name);
	new->path = NULL;
	if (dir != NULL)
	{
		if (dir[ft_strlen(dir) - 1] != '/')
			tmp = ft_strjoin(dir, "/");
		else
			tmp = ft_strdup(dir);
		new->path = ft_strjoin(tmp, name);
		lstat(new->path, &lbuf);
		free(tmp);
	}
	else
		lstat(name, &lbuf);
	new->time = (opt & CTIME) ? lbuf.st_ctim : lbuf.st_mtim;
	new->time = (opt & ATIME) ? lbuf.st_atim : new->time;
	//new->time = (opt & BTIME) ? lbuf.st_birthtim : new->time;
	ft_set_newdata(&new, lbuf);
	return (new);
}

t_data				*ft_add(t_data **list, t_data *new)
{
	t_data			*ptr;

	if (!*list)
		*list = new;
	else
	{
		ptr = *list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (*list);
}
