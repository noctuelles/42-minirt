# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maabidal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 21:36:26 by maabidal          #+#    #+#              #
#    Updated: 2022/05/10 21:40:02 by maabidal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

INC = fractol.h

SRCS += test.c

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

CC = gcc -Wall -Wextra -Werror

MLX_LIB	= $(MLX_DIR)libmlx.a
ifeq ($(shell uname), Linux)
	MLX_DIR = ./mlx_x11/
	MLX_LNK	= -L $(MLX_DIR) -l mlx -lXext -lX11
else
	MLX_DIR = ./mlx_opengl/
	MLX_LNK	= -L $(MLX_DIR) -l mlx -framework OpenGL -framework AppKit
endif

LFT_DIR = ./libft/
LFT_LIB = $(LFT_DIR)libft.a
LFT_LNK = -L $(LFT_DIR) -l ft

all: $(NAME)

$(NAME) : $(OBJS) $(MLX_LIB) $(LFT_LIB)
	$(CC) $(OBJS) $(MLX_LNK) $(LFT_LNK) -lm -o $(NAME)

$(OBJS): $(OBJS_DIR)%.o: %.c $(OBJS_DIR)
	$(CC) -I $(MLX_DIR) -I $(LFT_DIR) -c $< -o $@

$(OBJS_DIR):
	mkdir $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LFT_LIB):
	$(MAKE) -C $(LFT_DIR)

bonus : all

clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LFT_DIR)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LFT_DIR)

re: fclean all

.PHONY: all clean fclean re
