SOURCES			=	command_env.c command_export.c command_unset.c command_exit.c
SOURCES			+=	command_cd.c command_echo.c command_pwd.c
SOURCES			+=	utils_export_unset.c utils.c ft_sort_params.c

LIBFT	=	../libft/libft.a

OBJECTS			= $(SOURCES:.c=.o)

CC			= gcc
RM			= rm -rf
AR			= ar rcs
CFLAGS			= -Wall -Wextra -Werror -I. -g
NAME			= minishell_builtins.a

all: $(NAME) 

$(NAME): $(LIBFT) $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)
.c.o:
	gcc $(LIBFT)  -c $< -o $@ 
clean:
	$(RM) $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re
