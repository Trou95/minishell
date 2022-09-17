/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:29:36 by saksoy            #+#    #+#             */
/*   Updated: 2022/01/12 16:41:14 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int c)
{
	int	i;

	i = 0;
	if (c <= 0)
	{
		i = 1;
	}
	while (c)
	{
		i++;
		c = c / 10;
		if (c == 0)
			break ;
	}
	return (i);
}

static char	*sayiyapici(int n, int struzunluk, int rakam, char *str)
{
	while (struzunluk >= 0)
	{
		rakam = n % 10;
		str[struzunluk--] = rakam + 48;
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		struzunlugumuz;
	char	*str;
	int		rakamimiz;
	int		sign;

	struzunlugumuz = intlen(n);
	rakamimiz = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * struzunlugumuz + 1);
	if (!str)
		return (0);
	sign = 0;
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	str[struzunlugumuz--] = '\0';
	sayiyapici(n, struzunlugumuz, rakamimiz, str);
	if (sign == -1 && str[0] == '0')
		str[0] = '-';
	return (str);
}
