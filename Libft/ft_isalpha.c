/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:51:02 by mgordag          #+#    #+#              */
/*   Updated: 2022/01/27 14:51:04 by mgordag         ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))
		return (0);
	return (1);
}
/*
#include <stdio.h>
int	main(void)
{
	int a;

	a = 107;
	printf("%d", ft_isalpha(a));
	return 0;
}
*/
