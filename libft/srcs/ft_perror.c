/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:57:50 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:57:59 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_puterror(char *m)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(m);
}

void			ft_perror(char *m)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(m);
	exit(-1);
}

int				fts_open(char **av)
{
	int			i;

	i = 0;
	while (av[i])
		if (ft_strcmp(av[i++], "") == 0)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putendl_fd("fts_open: No such file or directory", 2);
			return (-1);
		}
	return (0);
}
