NAME		=	miniRT

SRCS		=	test.c

_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix objs/, $(_OBJS))
DEPS		=	$(OBJS:%.o=%.d)


CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -MMD

INCLUDE		=	-I ./srcs/\
				-I ./srcs/mlx_x11/\
				-I ./srcs/parsing

LIBS		=	srcs/mlx_x11/libmlx.a#srcs/libft/libft.a\
				

LIBS_EXT	=	-lm -lXext -lX11


all		:	$(NAME)

-include $(DEPS)
objs/%.o	:	srcs/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${CFLAGS} ${INCLUDE} -c ./$< -o $@

$(NAME)	:	$(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBS_EXT) -o $(NAME)

$(LIBS)	:	FORCE
	@for lib in $(LIBS); do\
		echo $(MAKE) -C $$(dirname $$lib);\
		$(MAKE) -C $$(dirname $$lib);\
	done

clean	:	
	rm -Rf objs/

cleanlibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) clean;\
		make -C $$(dirname $$lib) clean;\
	done

cleanall	:	clean cleanlibs


fclean	:	clean
	rm -f ${NAME}

fcleanlibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) fclean;\
		make -C $$(dirname $$lib) fclean;\
	done

fcleanall	:	fclean fcleanlibs


re		:	fclean ${NAME}

relibs	:	
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) re;\
		make -C $$(dirname $$lib) re;\
	done

reall	: relibs re


bonus	:	$(NAME)

.PHONY	:	all clean cleanlibs cleanall fclean fcleanlibs fcleanall re relibs reall FORCE bonus
