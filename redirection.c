#include "minishell.h"

void	last_infile(t_redirection *new, char *redir)
{
	while (new)
	{
		redir = new->redir;
		if (!ft_strcmp(redir, "<"))
		{
			g_data.infiles[new->in_index] = open(new->args, O_RDONLY);
			if (g_data.infiles[new->in_index] == -1)
				perror("Opening file error");
			if (dup2(g_data.infiles[new->in_index], 0) == -1)
				perror("Error on dup2");
			if (close(g_data.infiles[new->in_index]))
				perror("Error on closing infile");
		}
		else if (!ft_strcmp(redir, "<<"))
		{
			if (dup2(g_data.heredoc[new->her_index][0], 0) == -1)
				perror("Error on dup2");
			if (close(g_data.heredoc[new->her_index][0]))
				perror("Error on closing infile");
		}
		new = new->next;
	}
}

void	dup_outfile(int fd_out)
{
	if (dup2(g_data.outfiles[fd_out], 1) == -1)
		perror("Error on dup2");
	if (close(g_data.outfiles[fd_out]) == -1)
		perror("Error on closing file");
}

void	last_outfile(t_redirection *new, char *redir)
{
	while (new)
	{
		redir = new->redir;
		if (!ft_strcmp(redir, ">"))
		{
			g_data.outfiles[new->out_index] = open(new->args,
					O_CREAT | O_TRUNC | O_RDWR, 0777);
			if (g_data.outfiles[new->out_index] == -1)
				perror("Opening file error");
			dup_outfile(new->out_index);
		}
		else if (!ft_strcmp(redir, ">>"))
		{
			g_data.outfiles[new->out_index] = open(new->args,
					O_CREAT | O_RDWR | O_APPEND, 0777);
			if (g_data.outfiles[new->out_index] == -1)
				perror("Opening file error");
			dup_outfile(new->out_index);
		}
		new = new->next;
	}
}

void	redirection(t_syntax_tree *tree)
{
	char			*redir;
	t_redirection	*new;

	new = tree->s_redir;
	redir = NULL;
	last_infile(new, redir);
	new = tree->s_redir;
	last_outfile(new, redir);
}
