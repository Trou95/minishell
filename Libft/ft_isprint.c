/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:52:30 by mgordag           #+#    #+#             */
/*   Updated: 2022/01/27 14:52:31 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	return (1);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main()
{
	int a;
	
	a = 41;
	printf("%d \n", ft_isprint(a));
	printf("%d \n", isprint(a));
	return 0;
}
*/
