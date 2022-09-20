#include "parser_strutils.h"


int ft_str_clearspace_end(const char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] == ' ')
		i++;
	return i;
}

char *ft_str_clearspace(const char *str)
{
	int i;
	char *ret;
	char *tmp;

	ret = malloc(sizeof(char));
	i = 0;
	while(str[i])
	{
		if(str[i] == '"')
		{
			tmp = ft_substr(str, i , parser_quote_endidx(&str[i + 1], '"') + 2);
			i += ft_strlen(tmp) + 2;
			ret = ft_free_strjoin(ret, tmp);
		}
		else
		{
			tmp = ft_substr(str, i, 1);
			ret = ft_free_strjoin(ret, tmp);
			i += (str[i] != ' ') + ft_str_clearspace_end(&str[i]);
		}
		free(tmp);
	}
	return ret;
}