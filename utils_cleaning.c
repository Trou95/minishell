/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:08:29 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 18:16:53 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_freeall(void *arg)
{
	int	i;
	t_arg *tmp_arg;
	
	i = 0;
	tmp_arg = (t_arg *)arg;
	if (g_data.infiles)
		free(g_data.infiles);
	if (g_data.outfiles)
		free(g_data.outfiles);
	if (g_data.heredoc)
	{
		while (i < g_data.count_her)
		{
			if (g_data.heredoc[i])
				free(g_data.heredoc[i]);
				i++;
		}
		free(g_data.heredoc);
	}
	free(g_data.pids);
	free(arg);
	return (1);
}
