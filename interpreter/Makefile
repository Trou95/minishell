NAME = minishell
SRC = *.c

all: $(NAME)

$(NAME) : $(SRC) 
		gcc $(SRC) ./Libft/libft.a -L/usr/include -lreadline -o $(NAME)

clean:
	rm $(NAME)