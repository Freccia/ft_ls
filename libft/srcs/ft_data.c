/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:41:48 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:52:27 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			ft_getdirs(t_data **data, char *name, int opt)
{
	struct stat		sbuf;
	struct stat		lbuf;
	int				ret;

	ret = lstat(name, &lbuf);
	if ((stat(name, &sbuf) == -1 && ret == -1) || opt & OPT_D)
		return ;
	if (S_ISDIR(lbuf.st_mode))
		ft_add(data, ft_newdata(name, NULL, opt));
	else if (S_ISLNK(lbuf.st_mode) && !(opt & LONG) && S_ISDIR(sbuf.st_mode))
		ft_add(data, ft_newdata(name, NULL, opt));
}

static void			ft_getfiles(t_data **data, char *name, int opt, int *err)
{
	struct stat		sbuf;
	struct stat		lbuf;
	int				ret;

	ret = lstat(name, &lbuf);
	if (stat(name, &sbuf) == -1 && ret == -1 && (*err = 1))
		return ;
	if ((opt & LONG) && !S_ISDIR(lbuf.st_mode))
		ft_add(data, ft_newdata(name, NULL, opt));
	else if ((opt & OPT_D) && S_ISDIR(sbuf.st_mode))
		ft_add(data, ft_newdata(name, NULL, opt));
	else if (!S_ISDIR(lbuf.st_mode))
	{
		if (!S_ISLNK(lbuf.st_mode))
			ft_add(data, ft_newdata(name, NULL, opt));
		else if (S_ISLNK(lbuf.st_mode) && !S_ISDIR(sbuf.st_mode))
			ft_add(data, ft_newdata(name, NULL, opt));
	}
}

t_data				*ft_data(t_env *env, t_data *args, int mode)
{
	t_data			*data;
	t_data			*ptr;

	ptr = args;
	data = NULL;
	while (ptr)
	{
		if (mode == D)
			ft_getdirs(&data, ptr->name, env->opt);
		else if (mode == F)
			ft_getfiles(&data, ptr->name, env->opt, &env->err);
		ptr = ptr->next;
	}
	return (data);
}
