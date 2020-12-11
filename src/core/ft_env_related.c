/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_related.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:32:29 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/11 11:55:03 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_getvar(t_shell *shell, char *search)
{
	int		i;
	int		len;
	char	*tofree;

	i = 0;
	len = ft_strlen(search) + 1;
	while (shell->env && shell->env[i] != NULL)
	{
		tofree = ft_substr(shell->env[i], 0, len - 1);
		if (ft_strcmp(tofree, search) == 0)
			return (ft_substr(shell->env[i], len, ft_strlen(shell->env[i])));
		free(tofree);
		i++;
	}
	return (ft_strdup(""));
}

int		ft_len(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i] != NULL)
		i++;
	return (i);
}

void	ft_addvar(t_shell *shell, char *var)
{
	int		len;
	int		i;
	char	**newenv;

	len = ft_len(shell->env);
	newenv = (char**)malloc(sizeof(char*) * (len + 2));
	i = 0;
	while (shell->env && shell->env[i] != NULL)
	{
		newenv[i] = shell->env[i];
		i++;
	}
	newenv[i++] = var;
	newenv[i] = NULL;
	free(shell->env);
	shell->env = newenv;
}
