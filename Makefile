# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/26 17:34:20 by mfilipch          #+#    #+#              #
#    Updated: 2016/10/26 17:34:22 by mfilipch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

FUNCS		+=	main.c\
				hooks.c\
				ft_read.c\
				ft_draw.c\
				process.c\
				textures.c\
				raycast.c

OBJS		=	$(addprefix $(OBJS_DIR), $(FUNCS:.c=.o))

LIB			=	./libft/libft.a
LIBINC		=	-I./libft
LIBLINK		=	-L./libft -lft

MLX			=	./minilibx/libmlx.a
MLXINC		=	-I./minilibx
MLXLINK		=	-L./minilibx -lmlx -framework OpenGL -framework AppKit

OBJS_DIR 	=	./build/
INC_DIR 	=	./includes/

CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra

ifdef ALLOCWRAP
	LDFLAGS += ./alloc_wrap.c -ldl
endif

.PHONY: all clean flcean $(NAME) re 

all: $(NAME)

build:
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: %.c | build
	@$(CC) $(FLAGS) $(LIBINC) $(MLXINC) -I $(INC_DIR) -c $< -o $@

$(LIB):
	@make -C ./libft

$(MLX):
	@make -C ./minilibx

$(NAME): $(LIB) $(MLX) $(OBJS)
	@$(CC) $(FKAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBLINK) $(MLXLINK) 

clean:
	@/bin/rm -rf $(OBJS_DIR)
	@make -C ./libft clean
	@make -C ./minilibx clean
	@/bin/rm -f *.out
	@/bin/rm -f ._*
	@/bin/rm -f .DS*
	@/bin/rm -f ./includes/._*
	@/bin/rm -f ./includes/.DS*
	@/bin/rm -f ./textures/._*
	@/bin/rm -f ./textures/.DS*
	@/bin/rm -f ./sound/._*
	@/bin/rm -f ./sound/.DS*
	@/bin/rm -f ./music/._*
	@/bin/rm -f ./music/.DS*

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
