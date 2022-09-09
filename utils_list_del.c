#include "minishell.h"

void	del_s_syntax_tree(t_syntax_tree *del)
{
	del_s_command(del->s_command);
	del_s_redirection(del->s_redir);
	free(del);
}

void	del_s_command(t_command *del)
{
	int	i;

	i = -1;
	if (!del)
		return ;
	while (del->command[++i])
		ft_bzero(del->command[i], ft_strlen(del->command[i]));
	i = -1;
	while (del->command[++i])
		free(del->command[i]);
	if (del->command)
		free(del->command);
	free(del);
}

void	del_s_redirection(t_redirection *del)
{
	t_redirection *iter;
	
	if (!del)
		return ;
	while (del)
	{
		iter = del;
		del = del->next;
		ft_bzero(iter->redir, ft_strlen(iter->redir));
		ft_bzero(iter->args, ft_strlen(iter->args));
		free(iter->redir);
		free(iter->args);
		free(del);
	}
	free(iter);
}

void del_list_left_side(t_syntax_tree *list_iter)
{
	t_syntax_tree *temp;

	temp = list_iter; 
	while (temp->left)
		temp = temp->left;
	while (temp != list_iter)
	{
		temp = temp->prev;
		del_s_syntax_tree(temp->left);
		if (temp->right && temp != list_iter)
			del_s_syntax_tree(temp->right);
	}
}

void del_list_right_side(t_syntax_tree *list_iter)
{
	t_syntax_tree *temp;

	while (list_iter->right)
	{
		list_iter = list_iter->right;
		if (list_iter->left)
			del_list_left_side(list_iter);
	}
	while (list_iter->prev)
	{
		temp = list_iter;
		list_iter = list_iter->prev;
		del_s_syntax_tree(temp);
	}
}

void	del_list(t_syntax_tree *list)
{
	del_list_left_side(list);
	del_list_right_side(list);
	del_s_syntax_tree(list);
}