#include "minishell_builtins.h"

void	command_exit(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		;
	if (i > 1)
	{
		printf("exit\n");
		if (!arg[2])
			exit(ft_atoi(arg[1]));
		else
			printf("exit: too many arguments\n");
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
