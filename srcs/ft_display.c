/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 15:35:18 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:57:23 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			ft_put(t_data *data, int opt)
{
	t_data			*ptr;
	char			*ln;
	struct stat		buf;

	ptr = data;
	ln = NULL;
	while (ptr)
	{
		if (ptr->path && lstat(ptr->path, &buf) < 0)
			ft_puterror(ptr->path);
		else if (!ptr->path && lstat(ptr->name, &buf) < 0)
			ft_puterror(ptr->name);
		else if ((ptr->name && ptr->name[0] != '.') || (opt & ALL))
			ft_putendl(ptr->name);
		else if ((ptr->name && ptr->name[0] == '.') && (opt & OPT_D))
			ft_putendl(ptr->name);
		ptr = ptr->next;
	}
}

void				ft_readdir(char *dirpath, char *dirname, int opt)
{
	t_dir			*dir;
	t_dirent		*dirent;
	t_data			*file;
	t_data			*tmp;

	file = NULL;
	tmp = NULL;
	if ((dir = opendir(dirpath)) == NULL)
		return (ft_puterror((dirname) ? dirname : dirpath));
	while ((dirent = readdir(dir)) != NULL)
	{
		if (opt & ALL || dirent->d_name[0] != '.')
			ft_add(&file, ft_newdata(dirent->d_name, dirpath, opt));
		ft_add(&tmp, ft_newdata(dirent->d_name, dirpath, opt));
	}
	if (closedir(dir))
		ft_perror(dirpath);
	ft_sort(&file, opt);
	if (!ft_strcmp(dirname, ".") || (dirname && dirname[0] != '.') || opt & ALL)
		(opt & LONG) ? ft_put_long(&file, opt, 1) : ft_put(file, opt);
	(opt & RECURSIVE) ? ft_recursive(&tmp, opt) : NULL;
	ft_datafree(file);
	ft_datafree(tmp);
}

static void			ft_putdirs(t_data *dir, int opt, int putname)
{
	t_data			*ptr;

	ptr = dir;
	putname = (ptr && ptr->next) ? 1 : putname;
	while (ptr)
	{
		if (putname)
			ft_printf("%s:\n", ptr->name);
		ft_readdir(ptr->name, NULL, opt);
		if (ptr->next)
			ft_putchar('\n');
		ptr = ptr->next;
	}
}

void				ft_display(t_env *env)
{
	if (env->file)
	{
		if (env->opt & LONG)
			ft_put_long(&env->file, env->opt, 0);
		else
			ft_put(env->file, env->opt);
	}
	if (env->dir && env->file)
		ft_putchar('\n');
	if (env->dir)
		ft_putdirs(env->dir, env->opt, ((env->file || env->err) ? 1 : 0));
}
