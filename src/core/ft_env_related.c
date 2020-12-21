/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_related.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:32:29 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/21 09:06:08 by amoussai         ###   ########.fr       */
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
	newenv[i++] = ft_strdup(var);
	newenv[i] = NULL;
	free(shell->env);
	shell->env = newenv;
}

void	ft_deletevar(t_shell *shell, char *search)
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
			break ;
		free(tofree);
		i++;
	}
	if (shell->env[i] == NULL)
		return ;
	free(tofree);
	free(shell->env[i]);
	while (shell->env[i] != NULL)
	{
		shell->env[i] = shell->env[i + 1];
		i++;
	}
	free(shell->env[i]);
}
