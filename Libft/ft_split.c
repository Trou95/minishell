/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:07:30 by mgordag           #+#    #+#             */
/*   Updated: 2022/03/08 17:40:43 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h" 

int	ft_strmylen(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i + 1);
	return (i + 1);
}

int	ft_totalstrlen(const char *str, char c)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != '\0' && str[i + 1] != c)
			k++;
		i++;
	}
	return (k + 2);
}

void	createlist(int k, char **list, char *s, char c)
{
	int	j;
	int	i;

	i = 0;
	while (i < ft_totalstrlen(s, c) - 1 && s[k])
	{
		while (s[k] == c && s[k])
			k++;
		list[i] = (char *)malloc(sizeof(char) * ft_strmylen(&s[k], c));
		j = 0;
		while (s[k] != c && s[k])
		{
			list[i][j] = s[k];
			j++;
			k++;
		}
		if (j == 0)
			list[i] = 0;
		else
			list[i][j] = '\0';
		i++;
	}
	list[i] = 0;
}

char	**ft_split(const char *s, char c)
{
	int		k;
	char	**list;

	if (!s)
		return (NULL);
	list = (char **) malloc(sizeof (char *) * ft_totalstrlen(s, c));
	if (!list)
		return (0);
	k = 0;
	while (s[k] == c && s[k])
		k++;
	createlist(k, list, (char *)s, c);
	return (list);
}
