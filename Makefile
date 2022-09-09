SRCS			= main.c
RM				= rm -f
GCC				= gcc -Wall -Wextra -Werror
NAME			= minishell

all:			$(SRCS) $(NAME)


$(NAME): $(SRCS)
	@make -C Libft
	@$(GCC) $(SRCS) -L/usr/local/lib -I/usr/local/include -lreadline -o $(NAME)
	@echo Libft is compiled successfully
	@echo minishell is created successfully
clean:
	@$(RM) $(NAME)
	@echo minishell is removed successfully

fclean:			clean
	@make clean -C Libft

re:				fclean
	make


.PHONY:			all clean fclean re
