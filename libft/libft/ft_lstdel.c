/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:12:09 by lfabbro           #+#    #+#             */
/*   Updated: 2015/12/01 13:45:33 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*ret;

	ret = NULL;
	ret = *alst;
	while (ret)
	{
		tmp = ret;
		ret = ret->next;
		if (tmp)
			ft_lstdelone(&tmp, del);
	}
	*alst = NULL;
}
