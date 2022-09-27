#include "minishell_builtins.h"

void	command_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
}
