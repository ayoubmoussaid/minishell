/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:41:53 by amoussai          #+#    #+#             */
/*   Updated: 2019/11/02 08:28:37 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	if (*to_find == '\0')
		return ((char*)str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		k = i;
		while (str[k] != '\0' && to_find[j] != '\0' && str[k] == to_find[j])
		{
			if (k == len)
				return (0);
			k++;
			j++;
		}
		if (to_find[j] == '\0')
			return ((char*)&str[i]);
		i++;
	}
	return (0);
}
