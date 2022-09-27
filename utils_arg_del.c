#include "minishell.h"

void	del_arg(t_arg *args)
{
	int	i;

	i = -1;
	while (++i < args->cmd_count)
	{
		del_s_command(args->arg_commands[i]);
		del_s_redirection(args->arg_redirs[i]);
	}
	free(args->arg_commands);
	free(args->arg_redirs);
}
