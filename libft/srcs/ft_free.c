/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:46:51 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:47:07 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_datafree(t_data *data)
{
	t_data		*ptr;
	t_data		*tmp;

	ptr = data;
	while (ptr)
	{
		tmp = ptr;
		(tmp->name) ? free(tmp->name) : NULL;
		(tmp->path) ? free(tmp->path) : NULL;
		ptr = ptr->next;
		free(tmp);
	}
}

void			ft_freeenv(t_env *env)
{
	ft_datafree(env->dir);
	ft_datafree(env->file);
}
