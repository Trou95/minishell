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

void	*ft_space_cntrl(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return ((void *)1);
		i++;
	}
	return (NULL);
}
