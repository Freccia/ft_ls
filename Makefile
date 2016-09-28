# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/06 16:11:25 by lfabbro           #+#    #+#              #
#    Updated: 2016/09/22 13:23:41 by lfabbro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_NAME = ft_ls.c ft_data.c\
		   		   ft_list.c\
				   ft_sort.c\
				   ft_sortalpha.c\
				   ft_display.c\
				   ft_display_long.c\
				   ft_display_long2.c\
				   ft_recursive.c\
				   ft_options.c\
				   ft_mode.c\
				   ft_pad.c\
				   ft_perror.c\
				   ft_free.c

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB_NAMES = ftprintf

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/
LIB_PATH = ./libft/

CC = @gcc
CFLAGS = -Wall -Wextra -Werror

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

INC = $(addprefix -I,$(INC_PATH))

LIB_LINK = $(addprefix -L,$(LIB_PATH))
LIB = $(addprefix -l,$(LIB_NAMES))

.PHONY: all clean fclean re libre libclean libfclean

all:
	@make -C $(LIB_PATH)
	@make $(NAME)

$(NAME):
	@echo "\x1b[44;32m Making $(NAME) \x1b[0m"
	$(CC) $(CFLAGS) $(INC) $(LIB_LINK) $(LIB) $(SRC) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $^

clean:
	@echo "\x1b[44;31m Removing $(NAME) objects \x1b[0m"
	@/bin/rm -fr $(OBJ_PATH)

fclean: libfclean clean
	@echo "\x1b[44;31m Removing $(NAME) executable \x1b[0m"
	@/bin/rm -f $(NAME)

libre:
	@make -C $(LIB_PATH) re

libclean:
	@make -C $(LIB_PATH) clean

libfclean:
	@make -C $(LIB_PATH) fclean

re: fclean all
