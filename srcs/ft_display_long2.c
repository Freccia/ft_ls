/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_long2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 16:04:04 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/24 17:51:56 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_padding_majmin(int m, int pad)
{
	int				tpad;

	tpad = ft_nbrlen_base(m, 10);
	pad -= tpad;
	while (pad-- >= 0)
		ft_putchar(' ');
}

void				ft_display_uid(char *uid, int pad)
{
	ft_printf(" %s", uid);
	pad -= ft_strlen(uid);
	while (pad-- >= 0)
		ft_putchar(' ');
}

void				ft_display_gid(char *gid, int pad)
{
	ft_printf(" %s ", gid);
	pad -= ft_strlen(gid);
	while (pad-- > 0)
		ft_putchar(' ');
}

void				ft_display_time(t_timespec ttime, int opt)
{
	char			*time_long;
	time_t			cur_time;

	time_long = ctime(&ttime.tv_sec);
	time(&cur_time);
	if (time_long)
	{
		if (opt & FULLTIME)
			ft_printf("%.20s ", time_long + 4);
		else
		{
			ft_printf("%.3s ", time_long + 4);
			ft_printf("%.2s ", time_long + 8);
			if (ttime.tv_sec < cur_time - SIX_MONTHS || \
					ttime.tv_sec > cur_time + SIX_MONTHS)
				ft_printf(" %.4s ", time_long + 20);
			else
				ft_printf("%.5s ", time_long + 11);
		}
	}
	else
		ft_putstr("             ");
}

void				ft_display_size(struct stat *stat, t_pad pad)
{
	if (S_ISCHR(stat->st_mode) || S_ISBLK(stat->st_mode))
	{
		ft_padding_majmin(major(stat->st_rdev), pad.major);
		ft_printf(" %d,", major(stat->st_rdev));
		ft_padding_majmin(minor(stat->st_rdev), pad.minor);
		ft_printf("%d ", minor(stat->st_rdev));
	}
	else
	{
		pad.bytes -= ft_nbrlen_base(stat->st_size, 10);
		while (pad.bytes-- >= 0)
			ft_putchar(' ');
		ft_printf("%d ", stat->st_size);
	}
}
