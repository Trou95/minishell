SOURCES			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c
SOURCES			+=	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c
SOURCES			+=	ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c
SOURCES			+=	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c
SOURCES			+=	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c
SOURCES			+=	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c
SOURCES			+=	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c
SOURCES			+=	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c
SOURCES			+=	ft_tolower.c ft_toupper.c

SOURCES_BONUS		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c
SOURCES_BONUS		+=	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c
SOURCES_BONUS		+=	ft_lstmap.c ft_lstadd_back.c

OBJECTS			= $(SOURCES:.c=.o)
OBJECTS_BONUS		= $(SOURCES_BONUS:.c=.o)
CC			= gcc
RM			= rm -rf
AR			= ar rcs
CFLAGS			= -Wall -Wextra -Werror -I.
NAME			= libft.a

all:$(NAME) bonus

$(NAME):$(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)
 
bonus : $(OBJECTS_BONUS) $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS_BONUS) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re
