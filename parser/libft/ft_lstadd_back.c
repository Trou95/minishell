/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 04:00:48 by saksoy            #+#    #+#             */
/*   Updated: 2022/01/09 04:10:06 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*mlst;

	mlst = *lst;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (mlst->next != NULL)
		{
			mlst = mlst->next;
		}
		mlst->next = new;
	}
}
