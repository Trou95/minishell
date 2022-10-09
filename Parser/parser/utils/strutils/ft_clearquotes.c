#include "../parser_utils.h"

char	*ft_str_clearquotes(const char *str, char *ptr)
{
	int		i;
	int		n;
	char	c;

	i = 0;
	n = 0;
	printf("kol gibi str: _%s_\n",str);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			printf("c: %c\n",c);
			// yama
			
			//
			while (str[++i] && str[i] != c)
				ptr[n++] = str[i];
		}
		else
			ptr[n++] = str[i++];
	}
	return (ptr);
}
