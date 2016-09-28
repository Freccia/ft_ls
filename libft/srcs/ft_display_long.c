/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:42:22 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:46:22 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*ft_readlink(char *s)
{
	struct stat		lbuf;
	char			*ln;

	lstat(s, &lbuf);
	if (!S_ISLNK(lbuf.st_mode))
		return (NULL);
	ln = ft_strnew(256);
	if (readlink(s, ln, lbuf.st_size + 1 + 3) == -1)
		ft_perror(s);
	return (ln);
}

static void			ft_display_long(t_data **data, t_pad pad, int opt)
{
	char			*ln;
	struct stat		buf;

	ln = NULL;
	if ((*data)->path && lstat((*data)->path, &buf) == -1)
		return ;
	if (!(*data)->path && lstat((*data)->name, &buf) == -1)
		return ;
	ft_type(buf.st_mode);
	ft_permissions(buf.st_mode);
	ft_acl(((*data)->path) ? (*data)->path : (*data)->name);
	ft_nlinks(buf.st_nlink, pad.links);
	(!(opt & GROUP)) ? ft_display_uid((*data)->uid, pad.uid) : NULL;
	ft_display_gid((*data)->gid, pad.gid);
	ft_display_size(&buf, pad);
	ft_display_time((*data)->time, opt);
	ft_printf("%s", (*data)->name);
	if (S_ISLNK(buf.st_mode))
	{
		ln = ((*data)->path) ? ft_readlink((*data)->path) : \
				ft_readlink((*data)->name);
		ft_printf(" -> %s", ln);
		(ln) ? free(ln) : NULL;
	}
	ft_putchar('\n');
}

void				ft_put_long(t_data **data, int opt, int iftot)
{
	t_data			*ptr;
	t_pad			pad;

	ptr = *data;
	ft_setpad(data, &pad, opt);
	ft_tot_blocks(data, opt, iftot);
	while (ptr)
	{
		if (ptr->name[0] != '.' || opt & ALL)
			ft_display_long(&ptr, pad, opt);
		else if (ptr->name[0] == '.' || opt & OPT_D)
			ft_display_long(&ptr, pad, opt);
		ptr = ptr->next;
	}
}
