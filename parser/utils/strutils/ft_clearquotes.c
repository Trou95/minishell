#include "../parser_utils.h"

char *ft_str_clearquotes(const char *str, char *ptr)
{
	int i;
	int n;
	char c;

	i = 0;
	n = 0;
	while(str[i])
	{
		if(str[i] == '"' || str[i] == '\'' && (i == 0 || (i > 0 && str[i - 1] != '\\')))
		{
			c = str[i];
			while(str[++i] && str[i] != c)
			{
				if(str[i] == '\\')
					i++;
				ptr[n++] = str[i];
			}
		}
		else
		{
			if(str[i] == '\\')
				i++;
			ptr[n++] = str[i++];
		}
	}
	return ptr;
}