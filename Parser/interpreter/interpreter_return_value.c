#include "minishell_interpreter.h"


char	*ft_retvalue(int value)
{
	int		i;
	int		val;
	char	*ret;

	ret = ft_calloc(5, sizeof(char));
	i = 0;
	if (value < 0)
	{
		ret[i++] = '-';
		value = -value;
	}
	val = value;
	while (val)
	{
		val /= 10;
		i++;
	}
	while (value)
	{
		ret[--i] = value % 10 + '0';
		value /= 10;
	}
	return (ret);
}

/*
char* ft_format_retval(char *str,int retval)
{
	int i;
	char *ret;
	char *tmp;

	ret = ft_calloc(1, sizeof(char));
	i = 0;
	while(str[i])
	{
		if(str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_retvalue(retval);
			i += 2;
		}
		else
			tmp = ft_substr(str, i++, 1);

		ret = ft_free_strjoin(ret,tmp);
		free(tmp);
	}
	return ret;
}
*/