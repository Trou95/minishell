/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:32:46 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 09:32:47 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_utils.h"

char	*ft_free_strjoin(char *dst, const char *src)
{
	int		i;
	char	*ret;

	if (!dst || !src)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(dst) + ft_strlen(src) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (dst[++i])
		ret[i] = dst[i];
	while (*src)
		ret[i++] = *src++;
	ret[i] = '\0';
	free(dst);
	return (ret);
}
