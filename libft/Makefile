# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/27 11:20:09 by lfabbro           #+#    #+#              #
#   Updated: 2016/09/21 13:54:48 by lfabbro          ###   ########.fr         #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_NAME = ft_printf.c ft_pf_lenght.c ft_pf_parse.c ft_pf_set.c\
		   ft_pf_padding.c ft_pf_conversions.c ft_pf_handle_wchar.c\
		   ft_pf_formats_00.c ft_pf_formats_01.c ft_pf_a_char.c ft_pf_a_hex.c\
		   ft_pf_a_int.c ft_pf_a_octal.c ft_pf_a_ptr.c ft_pf_a_str.c\
		   ft_pf_a_uint.c ft_pf_a_wstr.c ft_pf_a_wchar.c

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_LIB_NAME = ft_strlen.o ft_strstr.o ft_strcpy.o ft_strdup.o ft_strndup.o\
			   ft_strcat.o ft_strcmp.o ft_strncpy.o ft_strncat.o ft_strlcat.o\
			   ft_strchr.o ft_strrchr.o ft_strnstr.o ft_strncmp.o ft_atoi.o\
			   ft_itoa_base.o ft_imaxtoa_base.o ft_uimaxtoa_base.o ft_itoa.o\
			   ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o\
			   ft_issticky.o ft_isalpha_str.o ft_isexec.o\
			   ft_toupper.o ft_tolower.o\
			   ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o\
			   ft_memmove.o ft_memchr.o ft_memcmp.o ft_memdel.o ft_strnew.o\
			   ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o\
			   ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o\
			   ft_strtrim.o ft_strxtrim.o ft_strsplit.o\
			   ft_strsplit_quote.o ft_strxtrim_quote.o\
			   ft_free_tab.o ft_tablen.o ft_tabnew.o ft_tabdup.o ft_tabndup.o\
			   ft_tabcpy.o ft_tabcat.o ft_tabpop.o\
			   ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o ft_puttab.o\
			   ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o\
			   ft_memalloc.o\
			   ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o\
			   ft_lstmap.o ft_wstrlen.o ft_abs.o ft_swap.o\
			   ft_realloc.o ft_getnbr.o ft_wchar_size.o\
			   ft_nbrlen.o ft_getchar.o ft_getchar.o\
			   ft_atol.o ft_atoll.o ft_isnbr.o\
			   get_next_line.o

LIB_NAME = ft
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes ./libft
LIB_PATH = ./libft/

CC = @gcc
CFLAGS = -Wall -Wextra -Werror


## SOURCES ##
OBJ_PRINTF = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_LIBFT = $(addprefix $(LIB_PATH),$(OBJ_LIB_NAME))

## INCLUDES ##
INC = $(addprefix -I,$(INC_PATH))

## LIBRARIES ##
LIB_LINK = $(addprefix -L,$(LIB_PATH))
LIB = $(addprefix -l,$(LIB_NAME))

.PHONY: makelibft clean fclean re norme

## RULES ##
all :
	@make -C $(LIB_PATH)
	@make $(NAME)

$(NAME): 
	@echo -e "\033[32;44m Making libprintf \033[0m"
	@make $(OBJ_PRINTF)
	@ar -rcs $(NAME) $(OBJ_LIBFT) $(OBJ_PRINTF)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean : libclean
	@/bin/rm -f $(OBJ_PRINTF)
	@/bin/rm -rf $(OBJ_PATH)

fclean : libfclean clean
	@/bin/rm -f $(NAME)

libclean :
	@make -C $(LIB_PATH) clean

libfclean :
	@make -C $(LIB_PATH) fclean

re : fclean all

norme :
	norminette **/*.[ch]
