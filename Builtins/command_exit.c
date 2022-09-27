#include "minishell_builtins.h"

void	command_exit(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		;
	if (i >= 1)
	{
		printf("exit\n");
		if (!(atoi(arg[1])))
		{
			printf("exit: %s: numeric argument required\n", arg[1]);
			exit(1);
		}
		if (atoi(arg[1]) && !arg[2])
			exit(atoi(arg[1]));
		else
			printf("exit: too many arguments\n");
	}
}
