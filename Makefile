# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/06 16:11:25 by lfabbro           #+#    #+#              #
#    Updated: 2016/11/14 19:47:15 by lfabbro          ###   ########.fr        #
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

LIB_NAMES = ft acl

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes ./libft/includes ./libft/libft
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
	@echo "\033[44;32m Making $(NAME) \033[0m"
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(NAME) $(LIB_LINK) $(LIB)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $^

clean:
	@echo "\033[44;31m Removing $(NAME) objects \033[0m"
	@/bin/rm -fr $(OBJ_PATH)

fclean: libfclean clean
	@echo "\033[44;31m Removing $(NAME) executable \033[0m"
	@/bin/rm -f $(NAME)

libre:
	@make -C $(LIB_PATH) re

libclean:
	@make -C $(LIB_PATH) clean

libfclean:
	@make -C $(LIB_PATH) fclean

re: fclean all
