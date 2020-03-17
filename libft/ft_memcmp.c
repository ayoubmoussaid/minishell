/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:27:31 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/18 16:42:55 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = s1;
	str2 = s2;
	if (str1 == NULL && str2 == NULL && n > 0)
		return (0);
	while (n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		else
		{
			str1++;
			str2++;
		}
	}
	return (0);
}
