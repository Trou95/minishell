#include "minishell.h"

void	ft_heredoc(char *arg)
{
	char	*str;

	pipe(g_data.heredoc[++g_data.ref_her]);
	while (1)
	{
		str = readline("heredoc> ");
		if (!ft_strcmp(str, arg))
		{
			free(str);
			break ;
		}
		write(g_data.heredoc[g_data.ref_her][1], str, ft_strlen(str));
		write(g_data.heredoc[g_data.ref_her][1], "\n", 1);
		free(str);
	}
	close(g_data.heredoc[g_data.ref_her][1]);
}

void	isheredoc(t_syntax_tree *tree)
{
	t_redirection	*new;
	char			*redir;

	new = tree->s_redir;
	while (new)
	{
		redir = new->redir;
		if (!ft_strcmp(redir, "<<"))
			ft_heredoc(new->args);
		new = new->next;
	}
}

void	all_heredocs(t_syntax_tree *tree)
{
	if (tree->type == EXEC)
	{
		if (tree->right)
			isheredoc(tree->right);
	}
	else
	{
		if (tree->left->right)
			isheredoc(tree->left->right);
		if (tree->right->type == PIPE)
			all_heredocs(tree->right);
		else
		{
			if (tree->right->right)
				isheredoc(tree->right->right);
		}
	}
}
