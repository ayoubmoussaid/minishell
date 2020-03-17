/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 13:49:17 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/20 11:28:48 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int n;

	n = 0;
	while (dest[n] != '\0')
		n++;
	i = n;
	while (src[i - n] != '\0')
	{
		dest[i] = (char)src[i - n];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
