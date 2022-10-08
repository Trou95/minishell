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
	char	*cmd_path;

	if (is_builtin(left->s_command->command[0]))
	{
		before_execve(right);
		exit(which_builtin(left->s_command->command));
	}
	else
	{
		if (ft_strrchr(left->s_command->command[0], '/'))
		{
			if (!command_w_path(left->s_command->command))
				exit(g_data.exit_num);
		}
		path_operations(&cmd_path, left);
		before_execve(right);
		if (g_data.redir_val)
		{
			execve(cmd_path, left->s_command->command, g_data.env);
			exit(1);
		}
		else
			exit(g_data.exit_num);
	}
}

void	main_process(int *fd)
{
	if (dup2(fd[0], 0) == -1)
		perror("Error on dup2");
	if (close(fd[0]) == -1)
		perror("Error on closing file");
	if (close(fd[1]) == -1)
		perror("Error on closing file");
}

void	before_execute(t_syntax_tree *tree)
{
	t_syntax_tree	*left;
	t_syntax_tree	*right;

	g_data.cmd++;
	left = tree->left;
	right = tree->right;
	if (g_data.pipe < g_data.cmd_count - 1)
		pipe(g_data.fd[g_data.pipe]);
	if (g_data.cmd_count == 1 && is_builtin(left->s_command->command[0]))
	{
		if (right)
			redirection(right);
		g_data.exit_num = which_builtin(left->s_command->command);
	}
	else
	{
		g_data.pids[g_data.cmd] = fork();
		if (g_data.pids[g_data.cmd] == -1)
			perror("Error on fork");
		if (g_data.pids[g_data.cmd] == 0)
			child_process(left, right);
		if (g_data.pipe < g_data.cmd_count - 1)
			main_process(g_data.fd[g_data.pipe]);
	}
}

void	executer(t_syntax_tree *tree)
{
	int	i;

	i = 0;
	if (tree->type == EXEC)
		voyage_on_tree(tree);
	else
	{
		voyage_on_tree(tree->left);
		if (tree->right->type == PIPE)
			executer(tree->right);
		else
			voyage_on_tree(tree->right);
	}
	while (g_data.cmd_count - i >= 0)
	{
		waitpid(g_data.pids[g_data.cmd_count - i], &g_data.exit_num, 0);
		if (WIFEXITED(g_data.exit_num))
			g_data.exit_num /= 256;
		i++;
	}
}
