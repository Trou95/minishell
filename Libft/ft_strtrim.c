/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:13:25 by mgordag           #+#    #+#             */
/*   Updated: 2022/01/27 15:13:26 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;
	char	*new;

	s = 0;
	if (!s1)
		return (0);
	while (s1[s] && ft_strchr(set, s1[s]))
		s++;
	e = ft_strlen(s1) - 1;
	if (e)
		while (s1[e] && ft_strchr(set, s1[e]))
			e--;
	if (s > e + 1)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (e - s + 2));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1 + s, e - s + 2);
	return (new);
}
