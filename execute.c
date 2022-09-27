#include "minishell.h"

void	dup_files(int *fd)
{
	if (dup2(fd[1], 1) == -1)
		perror("Error on pipe dup2");
	if (close(fd[1]) == -1)
		perror("Error on closing file");
	if (close(fd[0]) == -1)
		perror("Error on closing file");
}

void	child_process(t_syntax_tree *left, t_syntax_tree *right)
{
	char	*path;
	char	*cmd_path;

	path = get_path(g_data.env);
	cmd_path = get_cmd(left->s_command->command[0], path);
	free(path);
	if (!cmd_path)
		perror("command not found");
	if (g_data.cmd % 2 == 1 && g_data.cmd < g_data.cmd_count)
		dup_files(g_data.fd);
	else if (g_data.cmd % 2 == 0 && g_data.cmd < g_data.cmd_count)
		dup_files(g_data.fd2);
	if (right)
		redirection(right);
	if (execve(cmd_path, left->s_command->command, g_data.env) == -1)
		perror("Execve error");
}

void	main_process(void)
{
	if (g_data.cmd % 2 == 1)
	{
		if (dup2(g_data.fd[0], 0) == -1)
			perror("Error on pipe dup2");
		if (close(g_data.fd[0]) == -1)
			perror("Error on closing file");
		if (close(g_data.fd[1]) == -1)
			perror("Error on closing file");
	}
	if (g_data.cmd % 2 == 0)
	{
		if (dup2(g_data.fd2[0], 0) == -1)
			perror("Error on pipe dup2");
		if (close(g_data.fd2[0]) == -1)
			perror("Error on closing file");
		if (close(g_data.fd2[1]) == -1)
			perror("Error on closing file");
	}
}

void	before_execute(t_syntax_tree *tree)
{
	t_syntax_tree	*left;
	t_syntax_tree	*right;
	pid_t			pid1;

	g_data.cmd++;
	left = tree->left;
	right = tree->right;
	if (g_data.cmd % 2 == 1)
	{
		if (pipe(g_data.fd) == -1)
			perror("Error on pipe");
		if (pipe(g_data.fd2) == -1)
			perror("Error on pipe2");
	}
	pid1 = fork();
	if (pid1 == -1)
		perror("Error on fork");
	if (pid1 == 0)
		child_process(left, right);
	else
	{
		waitpid(pid1, NULL, 0);
		free(g_data.cmd_path);
		main_process();
	}
}

void	executer(t_syntax_tree *tree)
{
	int pid;
	pid = fork();
	if (pid == 0)
	{
		if (tree->type == EXEC)
			before_execute(tree);
		else
		{
			before_execute(tree->left);
		if (tree->right->type == PIPE)
			executer(tree->right);
		else
			before_execute(tree->right);
		}
		return ;
	}	
}
