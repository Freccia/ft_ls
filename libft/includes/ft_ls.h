/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 10:20:20 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 11:07:18 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** dirent.h		:
**     		+opendir, +readdir, +closedir.
** grp.h		:
**     		+getgrgid.
** pwd.h 		:
**     		+getpwuid.
** time.h		:
**     		+time, +ctime.
**			minimum past   time (touch format) 190201000000 (Dec 31 1901)
**			maximum future time (touch format) 999912312359 (Dec 31 9999)
** stdio.h		:
**     		+perror.
** stdlib.h		:
**     		+malloc, +free, +exit.
** sys/acl.h	:
**     		+acl_get_file, +acl_free.
** sys/ioctl.h	:
**     		-ioctl.
** sys/stat.h	:
**     		+stat, +lstat.
** sys/xattr.h	:
**     		+listxattr, -getxattr.
** unistd.h		:
**     		+write, +readlink.
*/

# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <unistd.h>
# include "libft.h"

/*
** ----------------------  OPTIONS  -----------------------------
** |                                                            |
** | ALL:			'a'		ATIME:		'u'		GROUP:		'g' |
** | LONG:			'l'		CTIME:		'c'		DONTSORT:	'f' |
** | TIME:			't'		BTIME:		'U'		COLORS:		'G' |  <-- TODO
** | REVERSE: 		'r'		OPT_D:		'd'     FULLTIME:	'T' |
** | RECURSIVE: 	'R'		SIZE:		'S'                     |
** |                                                            |
** --------------------------------------------------------------
*/
# define ALL		1
# define LONG		4
# define TIME		8
# define REVERSE	16
# define RECURSIVE	32
# define ATIME		64
# define CTIME		128
# define BTIME		256
# define OPT_D		512
# define SIZE		1024
# define GROUP		2048
# define DONTSORT	4096
# define COLORS		8192
# define FULLTIME	16384

/*
**					**  PROJECT DEFINES  **
*/
# define D			1
# define F			2
# define SIX_MONTHS	15768000
# define ERROR		-1

typedef struct s_env			t_env;
typedef struct s_data			t_data;
typedef struct s_pad			t_pad;
typedef struct group			t_group;
typedef struct passwd			t_pwd;
typedef struct stat				t_stat;
typedef struct timespec			t_timespec;
typedef DIR						t_dir;
typedef struct dirent			t_dirent;

struct						s_env
{
	t_data				*dir;
	t_data				*file;
	int					opt;
	int					err;
};

struct						s_data
{
	char				*name;
	char				*path;
	t_timespec			time;
	long				size;
	char				*uid;
	char				*gid;
	t_data				*next;
};

struct						s_pad
{
	int					uid;
	int					gid;
	int					links;
	int					bytes;
	int					major;
	int					minor;
};

/*
**		FT_DATA
*/
t_data						*ft_data(t_env *env, t_data *args, int mode);

/*
**		FT_LIST
*/
void						ft_initpad(t_pad **pad);
t_data						*ft_newdata(char *name, char *dir, int opt);
t_data						*ft_add(t_data **list, t_data *new);

/*
**		FT_DISPLAY
*/
void						ft_display(t_env *env);
void						ft_readdir(char *dirpath, char *dirname, int opt);

/*
**		FT_DISPLAY_LONG
*/
char						*ft_readlink(char *s);
void						ft_padding_majmin(int m, int pad);
void						ft_display_uid(char *uid, int pad);
void						ft_display_gid(char *gid, int pad);
void						ft_display_time(t_timespec time, int opt);
void						ft_display_size(struct stat *stat, t_pad pad);
void						ft_put_long(t_data **data, int opt, int iftot);
void						ft_put_data(t_data *data);

/*
**		FT_RECURSIVE
**		FT_OPTIONS
**		FT_PAD
*/
void						ft_recursive(t_data **data, int opt);
int							ft_options(char **av, int *opt);
void						ft_setpad(t_data **data, t_pad *pad, int opt);

/*
**		FT_SORT
*/
void						ft_sort(t_data **data, int opt);
void						ft_swap_links(t_data *prev, t_data *tmp2,
		t_data *tmp1, t_data **data);
void						ft_sortalpha(t_data **data);
int							ft_datalen(t_data *data);

/*
**		FT_MODE
*/
int							ft_acl(char *path);
void						ft_tot_blocks(t_data **data, int opt, int iftot);
void						ft_type(mode_t mode);
void						ft_permissions(mode_t mode);
void						ft_nlinks(int links, int pad);

/*
**		FT_FREE
*/
void						ft_datafree(t_data *data);
void						ft_freeenv(t_env *env);

/*
**		FT_ERRORS
*/
void						ft_puterror(char *m);
void						ft_perror(char *m);
int							fts_open(char **av);

#endif
