#include "parser_utils.h"

int	ft_error(char *err_msg, char *err_arg, int err_type)
{
	if (err_msg)
	{
		if (err_arg)
			printf("Error: %s %s\n", err_msg, err_arg);
		else
			printf("Error: %s\n", err_msg);
	}
	if (err_type != 0)
		exit(err_type);
	return (0);
}

int	err_prnt(char *err_desc, char *err_code)
{
	printf("\033[1;33m%s\033[0m \033[1;31m%s\033[0m\n", err_desc, err_code);
	return (-1);
}

char	**amazing_split(char	*str)
{
	char	**ret;
	int		idx;
	int		len;
	int		line;
	ret = malloc(sizeof(char *) * 100);
	len = ft_strlen(str);
	line = -1;
	idx = -1;
	while (++idx < len)
	{
		if(str[idx] == '"')
		{
			ret[++line] = ft_substr(&str[idx], 0 ,ft_get_chrindex(&str[idx+1], '"') + 1);
			idx += ft_get_chrindex(&str[idx+1], '"') + 1;
		}
		if (str[idx] == ' ')
		{
			ret[++line] = ft_substr(&str[idx], 0 ,ft_get_chrindex(&str[idx+1], ' ') + 1);
			idx += ft_get_chrindex(&str[idx+1], ' ') + 1;
		}
	}
	return (ret);
}
