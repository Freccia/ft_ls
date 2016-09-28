/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:14:43 by lfabbro           #+#    #+#             */
/*   Updated: 2015/12/09 16:32:09 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*new_list;
	t_list	*tmp;

	new_list = NULL;
	while (lst)
	{
		tmp = f(lst);
		if (!new_list)
		{
			new_list = tmp;
			ret = new_list;
			new_list->next = NULL;
		}
		else
		{
			new_list->next = tmp;
			new_list = new_list->next;
			tmp->next = NULL;
		}
		lst = lst->next;
	}
	return (ret);
}
