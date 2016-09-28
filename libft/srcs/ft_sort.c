/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 11:00:34 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 11:04:48 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_datalen(t_data *data)
{
	int			len;
	t_data		*ptr;

	len = 0;
	ptr = data;
	while (ptr && ++len)
		ptr = ptr->next;
	return (len + 2);
}

static void			ft_sorttime(t_data **data)
{
	t_data		*prev;
	t_data		*ptr;
	int			time;

	time = ft_datalen(*data);
	while (time--)
	{
		prev = NULL;
		ptr = *data;
		while (ptr && ptr->next)
		{
			if (ptr->time.tv_sec < ptr->next->time.tv_sec || \
					(ptr->time.tv_sec == ptr->next->time.tv_sec && \
					ptr->time.tv_nsec < ptr->next->time.tv_nsec))
				ft_swap_links(prev, ptr, ptr->next, data);
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

static void			ft_sortsize(t_data **data)
{
	t_data		*prev;
	t_data		*ptr;
	int			time;

	time = ft_datalen(*data);
	while (time--)
	{
		prev = NULL;
		ptr = *data;
		while (ptr && ptr->next)
		{
			if (ptr->size < ptr->next->size)
				ft_swap_links(prev, ptr, ptr->next, data);
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

static void			ft_sortreverse(t_data **data)
{
	t_data		*rev;
	t_data		*tmp;

	rev = NULL;
	while (*data)
	{
		tmp = (*data)->next;
		(*data)->next = rev;
		rev = *data;
		(*data) = tmp;
	}
	*data = rev;
}

void				ft_sort(t_data **data, int opt)
{
	(!(opt & DONTSORT)) ? ft_sortalpha(data) : NULL;
	if (opt & TIME && !(opt & SIZE))
		ft_sorttime(data);
	if (opt & SIZE)
		ft_sortsize(data);
	if (opt & REVERSE)
		ft_sortreverse(data);
}
