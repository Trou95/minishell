/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:51:54 by mgordag          #+#    #+#              */
/*   Updated: 2022/01/27 14:51:56 by mgordag         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (c);
}
/*
#include <stdio.h>
int	main(void)
{
	int	a;

	a = 49;
	printf("%d", ft_isdigit(a));
	return 0;
}
*/
