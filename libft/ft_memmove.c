/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:38:21 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/20 15:13:13 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pd;
	const unsigned char	*ps;

	pd = dst;
	ps = src;
	if (pd == NULL && ps == NULL)
		return (NULL);
	if (ps < pd)
	{
		pd += len;
		ps += len;
		while (len--)
			*--pd = *--ps;
	}
	else
		while (len--)
			*pd++ = *ps++;
	return (dst);
}
