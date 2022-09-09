/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:00:03 by mgordag           #+#    #+#             */
/*   Updated: 2022/01/27 15:00:04 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stddef.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*a;

	if ((!dst && !src) || !n)
		return (dst);
	a = (char *)dst;
	while (n--)
	{
		*a = *(char *)src;
		a++;
		src++;
	}
	return (dst);
}
