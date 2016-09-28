/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 11:02:02 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 11:03:01 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int				ft_gid_pad(t_data **data, struct stat stat, int maxpad)
{
	t_group			*gid;
	int				pad;

	if ((gid = getgrgid(stat.st_gid)) != NULL)
		(*data)->gid = ft_strdup(gid->gr_name);
	else
		(*data)->gid = ft_itoa(stat.st_gid);
	pad = ft_strlen((*data)->gid);
	if (pad > maxpad)
		maxpad = pad;
	return (maxpad);
}

static int				ft_uid_pad(t_data **data, struct stat stat, int maxpad)
{
	t_pwd			*uid;
	int				pad;

	if ((uid = getpwuid(stat.st_uid)) != NULL)
		(*data)->uid = ft_strdup(uid->pw_name);
	else
		(*data)->uid = ft_itoa(stat.st_uid);
	pad = ft_strlen((*data)->uid);
	if (pad > maxpad)
		maxpad = pad;
	return (maxpad);
}

static int				ft_links_pad(struct stat stat, int maxpad)
{
	int				pad;

	pad = ft_nbrlen_base(stat.st_nlink, 10);
	if (pad > maxpad)
		maxpad = pad;
	return (maxpad);
}

static void				ft_bytes_pad(struct stat stat, t_pad **pad)
{
	int				bytes;
	int				tmp;

	bytes = 0;
	if (S_ISCHR(stat.st_mode) || S_ISBLK(stat.st_mode))
	{
		tmp = ft_nbrlen_base(major(stat.st_rdev), 10);
		if (tmp > (*pad)->major)
			(*pad)->major = tmp;
		tmp = ft_nbrlen_base(minor(stat.st_rdev), 10);
		if (tmp > (*pad)->minor)
			(*pad)->minor = tmp;
		bytes = (*pad)->major + (*pad)->minor + 3;
	}
	else
		bytes = ft_nbrlen_base(stat.st_size, 10);
	if (bytes > (*pad)->bytes)
		(*pad)->bytes = bytes;
}

void					ft_setpad(t_data **data, t_pad *pad, int opt)
{
	t_data			*ptr;
	struct stat		buf;

	ptr = (*data);
	ft_initpad(&pad);
	while (ptr)
	{
		if ((ptr->name[0] != '.' || opt & ALL)
				|| (ptr->name[0] == '.' && (opt & OPT_D)))
		{
			if (ptr->path)
				lstat(ptr->path, &buf);
			else
				lstat(ptr->name, &buf);
			pad->uid = ft_uid_pad(&ptr, buf, pad->uid);
			pad->gid = ft_gid_pad(&ptr, buf, pad->gid);
			pad->links = ft_links_pad(buf, pad->links);
			ft_bytes_pad(buf, &pad);
		}
		ptr = ptr->next;
	}
}
