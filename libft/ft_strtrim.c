/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:51:46 by amoussai          #+#    #+#             */
/*   Updated: 2019/11/02 09:25:40 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char *s1, char *set, int n, int m)
{
	int		start;
	int		i;
	char	ch;

	start = -1;
	while (++start < n)
	{
		i = -1;
		ch = s1[start];
		while (++i < m)
			if (set[i] == ch)
				break ;
		if (i == m)
			break ;
	}
	return (start);
}

static int	ft_end(char *s1, char *set, int n, int m)
{
	int		start;
	int		end;
	int		i;
	char	ch;

	start = 0;
	end = n;
	while (--end >= start)
	{
		i = -1;
		ch = s1[end];
		while (++i < m)
			if (set[i] == ch)
				break ;
		if (i == m)
			break ;
	}
	return (end);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int n;
	int m;
	int end;
	int start;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char*)s1);
	n = ft_strlen((char*)s1);
	m = ft_strlen((char*)set);
	start = ft_start((char*)s1, (char*)set, n, m);
	end = ft_end((char*)s1, (char*)set, n, m);
	if (end - start >= 0)
		return (ft_substr(s1, (unsigned int)start,
			(unsigned long)(end - start + 1)));
	else
		return (ft_substr(s1, (unsigned int)start,
			(unsigned long)(0)));
}
