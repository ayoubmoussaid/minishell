/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:32:29 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/11 10:33:39 by amoussai         ###   ########.fr       */
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
