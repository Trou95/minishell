# ca adssda  =	"\033[0;30m"
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
SRCS	=	main.c allocate_files.c cmd_utils.c errors.c execute.c heredoc.c redirection.c signal.c build_redirection.c utils_list_del_list.c utils_list_del_structs.c utils_list_new.c utils_tree_new.c utils_cleaning.c utils.c
CFLAGS	=
READLINEFLAGS	= 	-L./lib/readline/lib -lreadline
LIBFT	=	Libft/libft.a
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
	make re -C ./Parser

$(BUILTINS):
	make -C ./Builtins

$(NAME): $(SRCS) $(BUILTINS) $(READLINE) $(LIBFT) $(PARSER)
	@echo $(YELLOW) "Building... $(NAME)" $(END)
	@$(CC) $(SRCS) $(READLINEFLAGS) $(CFLAGS) -o $(NAME) $(LIBFT) $(BUILTINS) $(PARSER) -ggdb
	@echo $(GREEN) "$(NAME) created successfully!\n" $(END)

clean:
	@echo $(YELLOW) "Removing object files...$(NAME)" $(END)
	@make -C libft fclean
	@echo $(RED) "All files deleted successfully!\n" $(END)

fclean: clean
	@make -C ./Readline fclean
	@make -C ./Libft fclean
	@make -C ./Builtins fclean
	@make -C ./Parser fclean

re: clean all

norm :
	@make norm -C libft
	@norminette $(SRCS)

.PHONY: all, clean, fclean, re