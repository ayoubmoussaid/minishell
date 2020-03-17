/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:16:23 by amoussai          #+#    #+#             */
/*   Updated: 2019/10/18 22:08:57 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				n;
	unsigned int	i;
	char			*tab;

	if (s == NULL)
		return (NULL);
	n = ft_strlen((char*)s);
	tab = (char*)malloc(n + 1);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		tab[i] = f(i, s[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
