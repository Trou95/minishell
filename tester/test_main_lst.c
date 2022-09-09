/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksancako <ksancako@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:44:32 by ksancako          #+#    #+#             */
/*   Updated: 2022/09/07 13:44:34 by ksancako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_syntax_tree *bir;
	t_syntax_tree *iki;
	t_syntax_tree *uc;
	t_syntax_tree *dort;
    t_syntax_tree *bes;
    t_syntax_tree *alti, *yedi, *sekiz, *dokuz, *on , *onbir;
	char *str;
	char **m;

	str = ft_strdup("meryem uyuma");
	m = ft_split(str, ' ');
	
	bir = new_s_syntax_tree(PIPE);
	iki = new_s_syntax_tree(EXEC);
	uc = new_s_syntax_tree(COMMAND);
	uc->s_command =new_s_command(m);
	dort = new_s_syntax_tree(REDIR);
	dort->s_redir = new_s_redirection(ft_strdup("redir"), ft_strdup("args"));
	bes = new_s_syntax_tree(PIPE);
	alti = new_s_syntax_tree(EXEC);
	yedi = new_s_syntax_tree(COMMAND);
	sekiz = new_s_syntax_tree(REDIR);
	dokuz = new_s_syntax_tree(EXEC);
	on = new_s_syntax_tree(COMMAND);
	onbir = new_s_syntax_tree(REDIR);
	printf("noluyoo\n");
	
	bir->left = iki;
	iki->prev = bir;
	iki->left = uc;
	iki->right = dort;
	uc->prev = iki;
	dort->prev = iki;
	bir->right = bes;
	bes->prev = bir;
	bes->left = alti;
	alti->prev = bes;
	alti->left = yedi;
	yedi->prev = alti;
	alti->right = sekiz;
	sekiz->prev = alti;
	bes->right = dokuz;
	dokuz->prev = bes;
	dokuz->left = on;
	on->prev = dokuz;
	dokuz->right = onbir;
	onbir->prev = dokuz;
	
	del_all_list(bir);
	system("leaks a.out");
}
