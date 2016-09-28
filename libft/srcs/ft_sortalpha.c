/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortalpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 14:29:41 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 11:01:35 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_swap_links(t_data *prev, t_data *tmp2, t_data *tmp1,\
		t_data **data)
{
	tmp2->next = tmp1->next;
	tmp1->next = tmp2;
	if (prev)
		prev->next = tmp1;
	else
		*data = tmp1;
}

void				ft_putdata(t_data *data)
{
	t_data		*ptr;

	ptr = data;
	while (ptr && ptr->next)
	{
		ft_printf("%s - %s\n", ptr->name, ptr->next->name);
		ptr = ptr->next;
	}
	ft_printf("\n");
}

void				ft_sortalpha(t_data **data)
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
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
				ft_swap_links(prev, ptr, ptr->next, data);
			prev = ptr;
			ptr = ptr->next;
		}
	}
}
