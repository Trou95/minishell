SRC =  utils/*c \
		parser/*c \
	parser/utils/*c \
	parser/utils/strutils/*c \
	interpreter/*c \
	./*.c


OBJS = $(SRC:%.c=%.o)

LIBFT = ./libft/libft.a

NAME = minishell

CC = gcc

all: $(NAME)

$(NAME) : $(OBJS)
	@make -sC ./libft
	$(CC) -lreadline $(OBJS) $(LIBFT)  -ggdb -I./minishell.h -o $(NAME)

clean :
	@make fclean -C ./libft
	@rm -rf	./utils/*o
	@rm -rf	./parser/*o
	@rm -rf	./parser/utils/*o
	@rm -rf	./parser/utils/strutils/*o
	@rm -rf	./interpreter/*o
	@rm -rf	./*o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re all