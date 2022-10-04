#include "minishell.h"

int	ft_errors(int err_num)
{
	if (err_num == 0)
		;
	exit(err_num);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "env", 4) ||
        !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7) ||
        !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "cd", 3)||
        !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	which_builtin(char **command)
{
    int exit;

    exit = 0;
	if (!ft_strncmp(command[0], "echo", 5))
		exit = command_echo(command);
	else if (!ft_strncmp(command[0], "env", 4))
		exit = command_env(g_data.env);
	else if (!ft_strncmp(command[0], "pwd", 4))
		exit = command_pwd();
	else if (!ft_strncmp(command[0], "export", 7))
        exit = multiple_export(&g_data.export, &g_data.env, command);
    else if (!ft_strncmp(command[0], "unset", 6))
        exit = multiple_unset(&g_data.env, &g_data.export, command);
    else if (!ft_strncmp(command[0], "cd", 3))
        exit = command_cd(command[1], &g_data.export, &g_data.env);
    else if (!ft_strncmp(command[0], "exit", 5))
        command_exit(command);
    return (exit);
}