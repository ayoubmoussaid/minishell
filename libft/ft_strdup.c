/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:01:41 by amoussai          #+#    #+#             */
/*   Updated: 2019/11/02 08:26:02 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (src[i] != '\0')
		i++;
	str = (char*)malloc(i + 1);
	if (str)
	{
		i = 0;
		while (src[i] != '\0')
		{
			str[i] = src[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
