/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 14:05:43 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/12 14:07:17 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_env				*ft_newenv(void)
{
	t_env			*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_perror("malloc");
	env->dir = NULL;
	env->file = NULL;
	env->opt = 0;
	return (env);
}
