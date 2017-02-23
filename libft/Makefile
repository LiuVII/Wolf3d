# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/22 09:34:02 by mfilipch          #+#    #+#              #
#    Updated: 2016/10/09 23:56:07 by mfilipch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	libft.a
LIB_FUNCS	=	ft_isalpha.c\
				ft_isdigit.c\
				ft_isalnum.c\
				ft_isascii.c\
				ft_isprint.c
LIB_FUNCS	+=	ft_toupper.c\
				ft_tolower.c\
				ft_itoa.c\
				ft_atoi.c\
				ft_bzero.c
LIB_FUNCS	+=	ft_lstnew.c\
				ft_lstdelone.c\
				ft_lstdel.c\
				ft_lstadd.c\
				ft_lstiter.c\
				ft_lstmap.c
LIB_FUNCS	+=	ft_memalloc.c\
				ft_memchr.c\
				ft_memmove.c\
				ft_memcpy.c\
				ft_memccpy.c\
				ft_memcmp.c\
				ft_memdel.c\
				ft_memset.c
LIB_FUNCS	+=	ft_putchar.c\
				ft_putstr.c\
				ft_putendl.c\
				ft_putnbr.c\
				ft_putchar_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c
LIB_FUNCS	+=	ft_strcpy.c\
				ft_strncpy.c\
				ft_strcmp.c\
				ft_strequ.c\
				ft_strnequ.c\
				ft_strncmp.c\
				ft_strlen.c\
				ft_strstr.c\
				ft_strchr.c\
				ft_strrchr.c\
				ft_strnstr.c\
				ft_strcat.c\
				ft_strncat.c\
				ft_strlcat.c\
				ft_strnew.c\
				ft_strdup.c\
				ft_strdel.c\
				ft_strclr.c\
				ft_striter.c\
				ft_striteri.c\
				ft_strmap.c\
				ft_strmapi.c\
				ft_strjoin.c\
				ft_strsub.c\
				ft_strsplit.c\
				ft_strtrim.c

LIB_FUNCS	+= 	ft_atof.c\
				ft_strndup.c\
				ft_isspace.c\
				ft_power.c\
				ft_strnequ_ci.c\
				ft_bit_rev_print.c\
				ft_memprint.c\
				ft_mapmake.c\
				ft_mapfree.c\
				ft_strlcpy.c\
				ft_strnchr.c\
				ft_memrealloc.c\
				ft_lstremoveif.c\
				get_next_line.c\
				ft_lstclr.c

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LIB_OBJS	=	$(addprefix build/, $(LIB_FUNCS:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB_OBJS)
	@ar rcs $@ $^

build:
	@mkdir build

build/%.o: %.c libft.h | build
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@/bin/rm -rf build/
	@/bin/rm -f *.out
	@/bin/rm -f ._*
	@/bin/rm -f .DS*

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
