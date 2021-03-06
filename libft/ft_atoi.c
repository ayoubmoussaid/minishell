/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:08:59 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 14:04:09 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_isspace(char *str)
{
	while ((*str) != '\0')
	{
		if ((*str) == '\t' || (*str) == '\n' || (*str) == '\v' ||
		(*str) == '\f' || (*str) == '\r' || (*str) == ' ')
			str++;
		else
			return (str);
	}
	return (str);
}

long long		ft_atoi(const char *str)
{
	long long	res;
	int			neg;
	int			x;

	str = ft_isspace((char*)str);
	neg = 1;
	res = 0;
	x = 0;
	if ((*str) == '-')
		neg = -1;
	if ((*str) == '+' || (*str) == '-')
		str++;
	while (((*str) >= '0' && (*str) <= '9') && (*str) != '\0')
	{
		res = res * 10;
		res += *str - '0';
		if (++x > 19 && neg == 1)
			return (-1);
		else if (x > 19 && neg == -1)
			return (0);
		str++;
	}
	return (res * neg);
}
