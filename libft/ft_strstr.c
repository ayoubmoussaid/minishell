/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 11:00:23 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/20 11:38:10 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;
	int k;

	i = 0;
	if (*to_find == '\0')
		return ((char*)str);
	while (str[i] != '\0')
	{
		j = 0;
		k = i;
		while (str[k] != '\0' && to_find[j] != '\0' && str[k] == to_find[j])
		{
			k++;
			j++;
		}
		if (to_find[j] == '\0')
			return ((char*)&str[i]);
		i++;
	}
	return (0);
}
