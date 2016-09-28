/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:54:04 by lfabbro           #+#    #+#             */
/*   Updated: 2016/04/04 13:19:57 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "./libft.h"

# define BUFF_SIZE 10000
# define MAX_FD 2560
# define I_SIZE 2

typedef struct		s_save
{
	char			*buf;
	char			*ptr;
	long			buf_size;
	long			buf_len;
	long			line_len;
	int				ret;
}					t_save;

int					get_next_line(int const fd, char **line);

#endif
