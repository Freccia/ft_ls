/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:57:40 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:57:41 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_data		*ft_getargs(int ac, char **av, int opt)
{
	int			i;
	struct stat	buf;
	t_data		*args;

	i = 0;
	args = NULL;
	while (i <= ac && av[i])
	{
		if (lstat(av[i], &buf) == -1)
			ft_puterror(av[i]);
		ft_add(&args, ft_newdata(av[i++], NULL, opt));
	}
	return (args);
}

int					main(int ac, char **av)
{
	t_env		env;
	t_data		*args;
	int			cur;
	int			err;

	env.dir = NULL;
	env.file = NULL;
	env.err = 0;
	env.opt = 0;
	cur = ft_options(av, &env.opt);
	if (fts_open(av))
		return (-1);
	args = ft_getargs(ac, &av[cur], env.opt);
	env.dir = ft_data(&env, args, D);
	env.file = ft_data(&env, args, F);
	ft_datafree(args);
	if ((!env.dir && !env.file) && ac == cur)
		(env.opt & OPT_D) ? ft_add(&env.file, ft_newdata(".", NULL, env.opt))
			: ft_add(&env.dir, ft_newdata(".", NULL, env.opt));
	(!(env.opt & DONTSORT)) ? ft_sort(&env.dir, env.opt) : NULL;
	(!(env.opt & DONTSORT)) ? ft_sort(&env.file, env.opt) : NULL;
	ft_display(&env);
	err = env.err;
	ft_freeenv(&env);
	return (err);
}
