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
CC		=	gcc
SRCS	=	main.c allocate_files.c cmd_utils.c errors.c execute.c heredoc.c redirection.c signal.c utils_list_del_list.c utils_list_del_structs.c utils_list_new.c utils_tree_new.c utils.c
CFLAGS	=	-Wall -Wextra -Werror -I./lib/readline/include
LDFLAGS	= 	-L./lib/readline/lib -lreadline
LIBFT	=	libft/libft.a
LIB		= 	lib/.minishell
PARSER  = Parser/minishell_parser.a

all: $(NAME)

$(NAME): $(LIB) $(LIBFT) $(SRCS)
	@make -C ./Parser
	@echo $(YELLOW) "Building... $(NAME)" $(END)
	@$(CC) $(SRCS) $(LDFLAGS) -o $(NAME) $(LIBFT) $(PARSER) -ggdb
	@echo $(GREEN) "$(NAME) created successfully!\n" $(END)
$(LIBFT):
	@echo $(YELLOW) "Compiling..." Libft $(END)
	@make -C libft
$(LIB):
	@make -C ./lib
clean:
	@echo $(YELLOW) "Removing object files...$(NAME)" $(END)
	@make -C libft fclean
	@echo $(RED) "All files deleted successfully!\n" $(END)
fclean: clean
	@make -C lib fclean
	@make -C libft fclean
re: clean all
norm :
	@make norm -C libft
	@norminette $(SRCS)
.PHONY: all, clean, fclean, re