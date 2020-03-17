/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:13:56 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/18 16:42:55 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c,
	size_t n)
{
	unsigned long	i;
	unsigned char	*strd;
	unsigned char	*strs;

	strd = (unsigned char*)dst;
	strs = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		if ((*strd++ = *strs++) == (unsigned char)c)
			return (strd);
		i++;
	}
	return (0);
}
