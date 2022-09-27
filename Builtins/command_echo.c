#include "minishell_builtins.h"

void	command_echo(char **str)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	if (!(ft_strncmp(str[1], "-n", 3)))
	{
		check = 0;
		i = 1;
	}
	while (str[++i])
		write(1, str[i], ft_strlen(str[i]));
	if (check)
		write(1, "\n", 1);
}
