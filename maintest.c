#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>


int	ft_get_chrindex(const char *str, char c)
{
    int	i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}

int	parser_quote_endidx(const char *str, char c)
{
    return (ft_get_chrindex(str, c));
}

int ft_get_qoueteend(char *str,char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            i += parser_quote_endidx(&str[i + 1], c) + 1;
        else if(str[i] == ' ')
            break;
        if(str[i])
            i++;
    }
    return i;
}

int main()
{
    while(1)
    {
        char *str = readline("> ");
        printf("%d %d %c\n", ft_get_qoueteend(str, '"'), str[ft_get_qoueteend(str,'"')],str[ft_get_qoueteend(str,'"')]);
    }
}

