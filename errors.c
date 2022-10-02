#include "minishell.h"

int	ft_errors(int err_num)
{
	if (err_num == 0)
		;
	exit(err_num);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "env", 3) || !ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "export", 6))
		return (1);
	return (0);
}

void	which_builtin(char **command)
{
	if (!ft_strncmp(command[0], "echo", 4))
		command_echo(command);
	else if (!ft_strncmp(command[0], "env", 3))
		command_env(g_data.env);
	else if (!ft_strncmp(command[0], "pwd", 3))
		command_pwd();
	else if (!ft_strncmp(command[0], "export", 6))
		command_export(&g_data.env, &g_data.exp, command[0]);
}