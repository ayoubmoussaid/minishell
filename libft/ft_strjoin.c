/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:38:44 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/25 15:39:58 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	n;
	unsigned int	m;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen((char*)s1);
	m = ft_strlen((char*)s2);
	newstr = (char*)malloc(n + m + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		newstr[i] = s1[i];
		i++;
	}
	while (i - n < m)
	{
		newstr[i] = s2[i - n];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
