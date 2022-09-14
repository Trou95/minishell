NAME = minishell
SRC = *.c

all: $(NAME)

$(NAME) : $(SRC)
		gcc $(SRC) -L/usr/include -lreadline -o $(NAME)

clean:
	rm $(NAME)