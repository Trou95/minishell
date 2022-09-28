#include "minishell.h"

void	del_list_left_side(t_syntax_tree *del)
{
	t_syntax_tree	*temp;

	temp = del;
	while (temp->left)
		temp = temp->left;
	while (temp != del)
	{
		temp = temp->prev;
		del_s_syntax_tree(temp->left);
		if (temp->right && temp != del)
			del_s_syntax_tree(temp->right);
	}
}

void	del_list_right_side(t_syntax_tree *del)
{
	t_syntax_tree	*temp;

	while (del->right)
	{
		del = del->right;
		if (del->left)
			del_list_left_side(del);
	}
	while (del->prev)
	{
		temp = del;
		del = del->prev;
		del_s_syntax_tree(temp);
	}
}

void	del_list(t_syntax_tree *list)
{
	del_list_left_side(list);
	del_list_right_side(list);
	del_s_syntax_tree(list);
}
