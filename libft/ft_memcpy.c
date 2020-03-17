/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:42:44 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/18 16:42:55 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long		i;
	unsigned char		*strd;
	const unsigned char	*strs;

	strd = dst;
	strs = src;
	i = 0;
	if (strd == NULL && strs == NULL && n > 0)
		return ((void*)NULL);
	while (i < n)
	{
		strd[i] = strs[i];
		i++;
	}
	return (dst);
}
