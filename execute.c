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
    int     redir_val;

    redir_val = 1;
    if (is_builtin(left->s_command->command[0]))
    {
        if (g_data.cmd < g_data.cmd_count - 1)
            dup_files(g_data.fd[g_data.pipe]);
        g_data.pipe++;
        if (right)
            redirection(right);
        exit(which_builtin(left->s_command->command));
    }
    else
    {
        path = get_path(g_data.env);
        cmd_path = get_cmd(left->s_command->command[0], path);
        free(path);
        if (!cmd_path)
        {
            write (2, left->s_command->command[0], ft_strlen(left->s_command->command[0]));
            write(2, ": command not found\n", 20);
            g_data.exit_num = 127;
        }
        if (g_data.cmd < g_data.cmd_count - 1)
            dup_files(g_data.fd[g_data.pipe]);
        g_data.pipe++;
        if (right)
            redir_val = redirection(right);
        if (redir_val)
        {
            execve(cmd_path, left->s_command->command, g_data.env);
            exit(0);
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
        which_builtin(left->s_command->command);
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
    int i;

    i = 0;
    if (tree->type == EXEC)
    {
        if (!tree->left)
            redirection(tree->right);
        else
            before_execute(tree);

    }
    else
    {
        if (!tree->left->left)
            redirection(tree->left->right);
        else
            before_execute(tree->left);
        if (tree->right->type == PIPE)
            executer(tree->right);
        else
        {
            if (!tree->right->left)
                redirection(tree->right->right);
            else
                before_execute(tree->right);
        }
    }
    while (g_data.cmd_count - i >= 0)
    {
        waitpid(g_data.pids[g_data.cmd_count - i], NULL, 0);
        i++;
    }
}
