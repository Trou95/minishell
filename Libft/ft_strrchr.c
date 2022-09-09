/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:13:05 by mgordag           #+#    #+#             */
/*   Updated: 2022/01/27 15:13:06 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	pos;

	pos = ft_strlen(s);
	if (!s)
		return (NULL);
	while (s[pos] != (char)c && pos >= 0)
		pos--;
	if (s[pos] == (char)c)
		return ((char *)&s[pos]);
	else
		return (NULL);
}
