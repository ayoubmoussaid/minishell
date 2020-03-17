/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:01:38 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/20 11:29:43 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	unsigned long i;
	unsigned long n;

	n = 0;
	while (dest[n] != '\0')
		n++;
	i = n;
	while (src[i - n] != '\0' && (i - n < nb))
	{
		dest[i] = src[i - n];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
