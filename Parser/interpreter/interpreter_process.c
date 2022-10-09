/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:42:17 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 09:42:21 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_interpreter.h"

char	**interpreter_array_format(char **arr, t_vars *g_data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		tmp = ft_check_quote(arr[i], g_data);
		if (tmp != NULL)
		{
			free(tmp);
			tmp = arr[i];
			printf("5\n");
			arr[i] = ft_check_quote(arr[i], g_data);
			printf("6\n");
			free(tmp);
		}
		i++;
	}
	printf("array-writer 1\n");
	array_writer(arr);
	printf("asdadsadad\n");
	return (arr);
}
