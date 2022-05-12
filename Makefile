NAME = miniRT

INC =	-I ./srcs\
		-I ./srcs/mlx_x11\
		-I ./srcs/parsing\
		-I ./srcs/libft

SRCS =	test.c

MLX = srcs/mlx_x11/libmlx_Linux.a
LIBFT = inc/libft/libft.a

CFLAGS = -Wall -Werror -Wextra
LIB = -lXext -lX11 -lm -lbsd

OBJDIR = objs
SRCDIR = srcs

OBJS = $(addprefix ${OBJDIR}/,${SRCS:.c=.o})

all : ${NAME}

mlx :
		@echo -n "Compiling minilibx"
		@make -s -C ./srcs/mlx_x11/ > /dev/null 2>&1
		@echo "\033[32m\t\t[OK]\033[0m"

libft :
		@echo -n "Compiling libft"
		@make -s -C srcs/libft
		@echo "\033[32m\t\t[OK]\033[0m"

$(NAME) : mlx ${OBJS}
		@echo -n  "Generating ${NAME}"
		@${CC} ${CFLAGS} ${OBJS} ${MLX} ${LIB} -o ${NAME} 
		@echo "\033[32m\t\t[OK]\033[0m"

bonus : $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		@mkdir -p ${@D}
		@${CC} ${CFLAGS} ${INC} -c $< -o $@
		
clean :	
		@echo -n "deleting mlx object files"
		@make clean -s -C srcs/mlx_x11 > /dev/null
		@echo "\033[32m\t[OK]\033[0m"
		@echo -n "deleting libft object files"
		@make clean -s -C srcs/libft > /dev/null
		@echo "\033[32m\t[OK]\033[0m"
		@echo -n "deleting object files"
		@rm -rf ${OBJDIR} > /dev/null
		@echo "\033[32m\t\t[OK]\033[0m"

fclean : clean
		@rm -rf ${NAME} ${MLX} ${LIBFT}
		@echo "full clean\033[32m\t\t\t[OK]\033[0m"

re : fclean all

.PHONY: all, clean, fclean, re, libft, test, bonus, mlx, testbonus
