/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 01:31:15 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/10 01:31:27 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_infile(int fd_in)
{
	if (dup2(g_data.infiles[fd_in], 0) == -1)
		perror("Error on dup2");
	if (close(g_data.infiles[fd_in]))
		perror("Error on closing infile");
}

void	dup_outfile(int fd_out)
{
	if (dup2(g_data.outfiles[fd_out], 1) == -1)
		perror("Error on dup2");
	if (close(g_data.outfiles[fd_out]) == -1)
		perror("Error on closing file");
}
