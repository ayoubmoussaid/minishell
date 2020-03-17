/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:59:02 by amoussai          #+#    #+#             */
/*   Updated: 2019/11/02 08:52:36 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start,
	size_t len)
{
	char	*sub;
	size_t	i;
	size_t	max;

	if (s == NULL)
		return (NULL);
	i = 0;
	max = ft_strlen(s);
	sub = (char*)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	while (start < max && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
