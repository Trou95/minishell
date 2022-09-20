#include "parser_strutils.h"

int ft_get_chrindex(const char* str, char c)
{
    int i;

    i = 0;
    while(str[i] && str[i] != c)
        i++;
    return i;
}