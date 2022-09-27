#include "minishell.h"

void	del_list_left_side(t_syntax_tree *list_iter)
{
	t_syntax_tree	*temp;

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

void	del_list_right_side(t_syntax_tree *list_iter)
{
	t_syntax_tree	*temp;

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
