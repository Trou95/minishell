/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:52:53 by mgordag           #+#    #+#             */
/*   Updated: 2022/03/08 16:09:24 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	intlen(int n)
{
	int	i;

	i = 0;
	while (n > 9)
	{
		n = (n / 10);
		i++;
	}
	return (i + 1);
}

void	inttochar(int a, char *s, unsigned int n)
{
	while (n > 9)
	{
		s[a] = n % 10 + '0';
		a--;
		n /= 10;
	}
	s[a] = n + '0';
}

char	*ismin(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 12);
	if (!str)
		return (0);
	str[0] = '-';
	inttochar(9, str, 214748364);
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

char	*isneg(int n)
{
	char	*str;
	int		a;

	n *= -1;
	a = intlen(n);
	str = (char *)malloc(sizeof(char) * (a + 2));
	if (!str)
		return (0);
	str[0] = '-';
	inttochar(a, str, n);
	str[a + 1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digit_counter;

	if (n == -2147483648)
		return (ismin());
	if (n < 0)
		return (isneg(n));
	digit_counter = intlen(n);
	str = (char *)malloc(sizeof(char) * (digit_counter + 1));
	if (!str)
		return (0);
	inttochar((digit_counter - 1), str, n);
	str[digit_counter] = '\0';
	return (str);
}
