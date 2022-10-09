RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[0;33m"
CYAN			=	"\033[0;35m"
BLUE			=	"\033[0;36m"
WHITE			=	"\033[0;37m"
END				=	"\033[0;0m"
# Files
NAME	=	minishell
CC		=	gcc -ggdb
SRCS	=	allocate_files.c \
build_redirection.c \
cmd_utils.c \
execute.c \
execute_utils.c \
heredoc.c \
main.c \
redirection.c \
signal.c \
utils.c \
utils_cleaning.c \
utils_list_del_list.c \
utils_list_del_structs.c \
utils_list_new.c \
utils_tree_new.c

OBJS = $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror
READLINEFLAGS	= -I./Readline/lib/readline/include	-L./Readline/lib/readline/lib  -lreadline
LIBFT	=	libft/libft.a
READLINE		= 	Readline/.minishell
PARSER  = Parser/minishell_parser.a
BUILTINS = Builtins/minishell_builtins.a

all: $(NAME)

$(READLINE):
	make -C ./Readline

$(LIBFT):
	@echo $(YELLOW) "Compiling..." Libft $(END)
	make -C libft

$(PARSER):
	make -C ./Parser

$(BUILTINS):
	make -C ./Builtins

.c.o:
	$(CC) -c $(CFLAGS) -I./Readline/lib/readline/include $<


$(NAME): $(BUILTINS) $(READLINE) $(LIBFT) $(PARSER) $(OBJS)
	@echo $(YELLOW) "Building... $(NAME)" $(END)
	$(CC) $(OBJS) $(READLINEFLAGS) $(CFLAGS) -o $(NAME) $(LIBFT) $(BUILTINS) $(PARSER) -ggdb
	@echo $(GREEN) "$(NAME) created successfully!\n" $(END)

clean:
	@make -C ./Libft fclean
	@make -C ./Builtins fclean
	@make -C ./Parser fclean
	rm -rf $(OBJS)

fclean: clean
	@make -C ./Readline fclean
	rm ./minishell

re: clean all

norm :
	@make norm -C libft
	@norminette $(SRCS)

.PHONY: all, clean, fclean, re
