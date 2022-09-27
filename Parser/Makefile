SRC =  $(wildcard utils/*c) \
		$(wildcard parser/*c) \
		$(wildcard parser/utils/*c) \
		$(wildcard parser/utils/strutils/*c) \
		$(wildcard interpreter/*c ) \
	


OBJS = $(SRC:.c=.o)

LIBFT = ../Libft/libft.a

NAME = minishell_parser.a

CFLAGS = 
CC = gcc

all: $(NAME)

$(NAME) : $(OBJS)
	@make -sC ../Libft
	ar	-rcs $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make fclean -C ../Libft
	@rm -rf	./utils/*o
	@rm -rf	./parser/*o
	@rm -rf	./parser/utils/*o
	@rm -rf	./parser/utils/strutils/*o
	@rm -rf	./interpreter/*o
	@rm -rf	./*o


fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re all