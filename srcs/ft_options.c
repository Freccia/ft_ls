/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:59:08 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 11:00:27 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			ft_error(char illopt)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(illopt, 2);
	ft_putendl_fd("\nusage: ft_ls [-acdglturRSTU1] [file ...]", 2);
	exit(-1);
}

static int			ft_parse_option2(char o)
{
	int		opt;

	opt = 0;
	if (o == 'a')
		opt = opt | ALL;
	else if (o == 'R')
		opt = opt | RECURSIVE;
	else if (o == 'r')
		opt = opt | REVERSE;
	else if (o == 'd')
		opt = opt | OPT_D;
	else if (o == 'f')
		opt = opt | DONTSORT | ALL;
	else if (o == 'g')
		opt = opt | GROUP | LONG;
	else if (o == 'T')
		opt = opt | FULLTIME;
	else if (o == 'G')
		opt = opt | COLORS;
	else if (o == 'S')
		opt = opt | SIZE;
	return (opt);
}

static int			ft_parse_option(char *o, int opt)
{
	int		ret;

	if (!o)
		return (-1);
	while (*o)
	{
		if (*o == 'l')
			opt = opt | LONG;
		else if (*o == '1')
			opt = (opt & LONG) ? opt ^ LONG : opt;
		else if (*o == 't')
			opt = opt | TIME;
		else if (*o == 'u')
			opt = (opt & ~CTIME & ~BTIME) | ATIME;
		else if (*o == 'c')
			opt = (opt & ~ATIME & ~BTIME) | CTIME;
		else if (*o == 'U')
			opt = (opt & ~ATIME & ~CTIME) | BTIME;
		else if ((ret = ft_parse_option2(*o)))
			opt = opt | ret;
		else
			ft_error(*o);
		++o;
	}
	return (opt);
}

int					ft_options(char **av, int *opt)
{
	int		i;

	i = 0;
	while (av[++i])
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == '\0')
				return (i);
			if (av[i][1] == '-')
			{
				if (av[i][2] == '\0')
					return (++i);
				ft_error('-');
			}
			*opt = *opt | ft_parse_option(&av[i][1], 0);
		}
		else
			break ;
	}
	return (i);
}
