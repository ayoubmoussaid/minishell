/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:41:42 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 16:15:36 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		ft_len(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i] != NULL)
		i++;
	return (i);
}

char	**get_env(t_env *env)
{
	char	**tab;
	int		len;
	t_env	*cur;
	int		i;

	len = 0;
	cur = env;
	while (cur)
	{
		len++;
		cur = cur->next;
	}
	len++;
	tab = (char**)malloc(sizeof(char*) * len);
	cur = env;
	i = 0;
	while (cur)
	{
		tab[i] = ft_specialjoin(cur->key, cur->value, '=');
		i++;
		cur = cur->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_specialjoin(char const *s1, char const *s2, char c)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	n;
	unsigned int	m;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen((char *)s1) + 1;
	m = ft_strlen((char *)s2);
	newstr = (char *)malloc(n + m + 1);
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (++i < n - 1)
		newstr[i] = s1[i];
	newstr[i++] = c;
	while (i - n < m)
	{
		newstr[i] = s2[i - n];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

void	free_env_var(t_env *del)
{
	free(del->key);
	free(del->value);
	free(del);
}
