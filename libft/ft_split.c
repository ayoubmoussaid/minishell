/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:48:53 by amoussai          #+#    #+#             */
/*   Updated: 2019/11/02 21:41:02 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_words(char *str, char c)
{
	int nbr;
	int i;

	nbr = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0' &&
			(str[i + 1] == c || str[i + 1] == '\0'))
		{
			i++;
			nbr++;
		}
		if (str[i] == '\0')
			return (nbr);
		i++;
	}
	return (nbr);
}

static int	ft_next_word_size(char *str, int k, char c)
{
	int word_size;

	word_size = 0;
	while (str[k] != c && str[k] != '\0')
	{
		word_size++;
		k++;
	}
	return (word_size);
}

static char	*my_str(char *str, int *k, char c)
{
	int		j;
	int		z;
	char	*new_str;

	j = 0;
	z = *k;
	new_str = (char*)malloc(sizeof(char) * (ft_next_word_size(str, z, c) + 1));
	if (!new_str)
		return (NULL);
	while (str[z] != c && str[z])
		new_str[j++] = str[z++];
	new_str[j] = '\0';
	*k = z;
	return (new_str);
}

static char	**free_tab(char **tab, int n)
{
	int i;

	i = 0;
	if (tab)
	{
		while (i < n)
			free(tab[i++]);
		free(tab);
	}
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	char	**new_str;
	char	*str;

	i = 0;
	k = 0;
	str = (char*)s;
	if (!str)
		return (NULL);
	new_str = (char**)malloc((ft_nbr_words(str, c) + 1) * sizeof(char*));
	if (!new_str)
		return (NULL);
	while (str[k])
	{
		while (str[k] == c && str[k])
			k++;
		if (str[k] && (new_str[i] = my_str(str, &k, c)) != NULL)
			i++;
		else if (str[k] && new_str[i] == NULL)
			return (free_tab(new_str, i));
	}
	new_str[i] = 0;
	return (new_str);
}
