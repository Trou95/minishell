/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:51 by mgordag           #+#    #+#             */
/*   Updated: 2022/03/09 13:16:40 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	d;

	c = ft_strlen(dst);
	if (dstsize <= c)
		return (dstsize + ft_strlen(src));
	d = 0;
	while (src[d] && (dstsize - c - 1 > 0))
		dst[c++] = src[d++];
	dst[c] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}
