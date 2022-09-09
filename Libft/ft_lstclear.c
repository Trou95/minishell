/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:53:45 by mgordag           #+#    #+#             */
/*   Updated: 2022/01/27 14:54:11 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*mlst;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		mlst = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = mlst;
	}
	*lst = NULL;
}
