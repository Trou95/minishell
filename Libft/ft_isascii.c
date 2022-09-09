/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:51:26 by mgordag          #+#    #+#              */
/*   Updated: 2022/01/27 14:51:29 by mgordag         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c <= 127 && c >= 0)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main()
{
	int	a;

	a = 128;
	printf("%d \n", ft_isascii(a));
	printf("%d", isascii(a));
	return (0);
}
*/
