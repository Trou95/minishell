/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:32:30 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 09:32:34 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_utils.h"

char	*ft_str_clearquotes(const char *str, char *ptr)
{
	int		i;
	int		n;
	char	c;

	i = 0;
	n = 0;
	printf("kol gibi str: _%s_\n",str);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			while (str[++i] && str[i] != c)
				ptr[n++] = str[i];
		}
		else
			ptr[n++] = str[i++];
	}
	return (ptr);
}
