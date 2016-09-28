/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 14:45:28 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 11:04:11 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_recursive(t_data **data, int opt)
{
	t_data			*ptr;
	struct stat		buf;

	ft_sort(data, opt);
	ptr = *data;
	while (ptr)
	{
		if (lstat(ptr->path, &buf) == -1)
			return ;
		if (S_ISDIR(buf.st_mode))
			if (ft_strcmp(ptr->name, ".") && \
					ft_strcmp(ptr->name, ".."))
			{
				if (!ft_strcmp(ptr->name, ".") || ptr->name[0] != '.'
						|| (opt & ALL))
				{
					ft_putchar('\n');
					ft_printf("%s:\n", ptr->path);
				}
				ft_readdir(ptr->path, ptr->name, opt);
			}
		ptr = ptr->next;
	}
}
