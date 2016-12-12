/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:57:30 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 11:06:39 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int						ft_acl(char *path)
{
	acl_t			md;

	if (listxattr(path, NULL, 0) > 0)
		return (ft_putchar('@'));
	if ((md = acl_get_file(path, ACL_TYPE_ACCESS)))
	{
		acl_free((void *)md);
		return (ft_putchar('+'));
	}
	acl_free((void *)md);
	return (ft_putchar(' '));
}

void					ft_nlinks(int nlinks, int maxpad)
{
	int				pad;

	pad = ft_nbrlen_base(nlinks, 10);
	while (pad++ < maxpad)
		ft_putchar(' ');
	ft_printf(" %d", nlinks);
}

void					ft_tot_blocks(t_data **data, int opt, int iftot)
{
	t_data			*ptr;
	struct stat		buf;
	int				tot;
	int				ret;

	ptr = *data;
	tot = 0;
	while (ptr)
	{
		ret = lstat(ptr->path, &buf);
		if (ret < 0)
		{
			ret = lstat(ptr->name, &buf);
		}
		if (ptr->name[0] != '.' || opt & ALL)
			iftot += (iftot > 0) ? 1 : 0;
		if (ptr->name[0] != '.' || opt & ALL)
			tot += buf.st_blocks;
		ptr = ptr->next;
	}
	if (iftot > 1)
		ft_printf("total %d\n", tot);
}

void					ft_type(mode_t mode)
{
	if (S_ISREG(mode))
		ft_printf("-");
	else if (S_ISDIR(mode))
		ft_printf("d");
	else if (S_ISCHR(mode))
		ft_printf("c");
	else if (S_ISBLK(mode))
		ft_printf("b");
	else if (S_ISLNK(mode))
		ft_printf("l");
	else if (S_ISFIFO(mode))
		ft_printf("p");
	else if (S_ISSOCK(mode))
		ft_printf("s");
	else
		ft_printf("u");
}

void					ft_permissions(mode_t mode)
{
	ft_printf((mode & S_IRUSR) ? "r" : "-");
	ft_printf((mode & S_IWUSR) ? "w" : "-");
	if (mode & S_IXUSR)
		ft_printf((mode & S_ISUID) ? "s" : "x");
	else
		ft_printf((mode & S_ISUID) ? "S" : "-");
	ft_printf((mode & S_IRGRP) ? "r" : "-");
	ft_printf((mode & S_IWGRP) ? "w" : "-");
	if (mode & S_IXGRP)
		ft_printf((mode & S_ISGID) ? "s" : "x");
	else
		ft_printf((mode & S_ISGID) ? "S" : "-");
	ft_printf((mode & S_IROTH) ? "r" : "-");
	ft_printf((mode & S_IWOTH) ? "w" : "-");
	if (mode & S_IXOTH)
		ft_printf((mode & S_ISVTX) ? "t" : "x");
	else
		ft_printf((mode & S_ISVTX) ? "T" : "-");
}
