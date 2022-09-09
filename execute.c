#include "minishell.h"

int	ft_size(char **lst)
{
	int i;

	i = -1;
	while (lst[++i])
		;
	return (i);
}

void	redirection(t_syntax_tree *tree)
{
	char			*temp;
	char			*read_doc;
	int				i;
	int				fd;
	t_redirection	*new;

	temp = tree->s_redir->redir;
	new = tree->s_redir;
	i = -1;
	g_data.files = malloc(ft_filesize(new) * sizeof(int));
	while (new)
	{
		temp = new->redir;
		if (!ft_strcmp(temp, "<")) // strcmp
		{
			if (g_data.files[++i] = open(new->args, O_RDONLY) == -1)
				perror("Opening file error");
			if (dup2(g_data.files[i], 0) == -1)
				perror("Error on dup2 infile");
		}
		else if (!ft_strcmp(temp, "<<"))
		{
			if (pipe(g_data.heredoc) == -1)
				perror("Error on pipe");
			if (dup2(g_data.heredoc[0], 0) == -1)
				perror("Error on heredoc dup2");
			if (dup2(g_data.heredoc[1], 1) == -1)
				perror("Error on heredoc dup2");
			read_doc = readline("heredoc> ");
			while (ft_strcmp(new->args, read_doc))
			{
				write(1, read_doc, ft_strlen(read_doc));
				write(1, "\n", 1);
				read_doc = readline("heredoc> ");
			}
		}
		else
		{
			if (!ft_strcmp(temp, ">")) // strcmp
			{
				if (g_data.files[++i] = open(new->args, O_CREAT | O_TRUNC | O_RDWR, 0000644) == -1)
					perror("Opening file error");
			}
			else if (!ft_strcmp(temp, ">>"))
			{
				if (g_data.files[++i] = open(new->args, O_CREAT | O_RDWR) == -1)
					perror("Opening file error");
			}
			if (dup2(g_data.files[i], 1) == -1)
				perror("Dup2 errror");
		}
		new = new->next;
	}
}

void	before_execute(t_syntax_tree *tree)
{
	t_syntax_tree	*left;
	t_syntax_tree	*right;
	pid_t			pid1;

	if ((pid1 = fork()) == -1)
		perror("Error on fork");
	if (dup2(g_data.fd[0], 0) == -1) //if mistake happens Muhammed will handle it
		perror("Error on closing file");
	if (pid1 == 0)
	{
		left = tree->left;
		if (tree->right)
			right = tree->right;
		g_data.path = get_path(g_data.env);
		g_data.cmd_path = get_cmd(left->s_command->command[0], &g_data);
		if (!g_data.cmd_path)
			perror("command not found");
		if (right)
			redirection(right);
		if (execve(g_data.cmd_path, left->s_command->command, g_data.env) == -1)
			perror("Execve error");
	}
	waitpid(pid1, NULL, 0);
}

void    executer(t_syntax_tree *tree)
{
	if (tree->type == EXEC)
		before_execute(tree);
	else
	{
		if (pipe(g_data.fd) == -1)
			perror("Error on pipe");
		if (dup2(g_data.fd[1], 1) == -1)
			perror("Error on pipe dup2");
		before_execute(tree->left);
		if (tree->right->type = PIPE)
			executer(tree->right);
		else
			before_execute(tree->right);
	}
}