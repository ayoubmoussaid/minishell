/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:41:42 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/02 10:39:19 by amoussai         ###   ########.fr       */
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

char **get_env(t_env *env)
{
	int len = 0;
	t_env *cur = env;
	while(cur)
	{
		len++;
		cur = cur->next;
	}
	len++;
	char **tab = (char**)malloc(sizeof(char*)*len);
	cur = env;
	int i = 0;
	while(cur)
	{
		tab[i] = ft_specialjoin(cur->key, cur->value, '=');
		//ft_putendl_fd(tab[i], 1);
		i++;
		cur = cur->next;
	}
	tab[i] = NULL;
	return tab;
}
