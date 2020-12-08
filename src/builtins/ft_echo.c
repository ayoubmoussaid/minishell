/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:24:53 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/08 09:34:55 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_getvar(t_shell *shell, char *search)
{
	int		i;
	int		len;
	char	*tofree;
	i = 0;
	len = ft_strlen(search);
	fprintf(shell->debug_file, "-- len: %d ---\n", len);
	while (shell->env && shell->env[i] != NULL)
	{
		//ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		tofree = ft_substr(shell->env[i], 0, len);
		//ft_putendl_fd(tofree, STDOUT_FILENO);
		//ft_putendl_fd("\n", STDOUT_FILENO);
		if (ft_strcmp(tofree, search) == 0)
			return (ft_substr(shell->env[i], len + 1, ft_strlen(shell->env[i])));
		free(tofree);
		i++;
	}
	return (ft_strdup(""));
}

void	ft_echo(t_shell *shell, char *args[])
{
	int		i;
	char	backline;
	char	*str;

	backline = '\n';
	i = -1;
	if (!args)
		ft_putendl_fd("", STDOUT_FILENO);
	else
	{
		if (ft_strcmp(args[0], "-n") == 0)
		{
			args++;
			backline = '\0';
		}
		while (args[++i] != NULL)
		{
			if (args[i][0] == '$')
			{
				str = ft_getvar(shell, &args[i][1]);
				ft_putstr_fd(str, STDOUT_FILENO);
				free(str);
			}
			else
				ft_putstr_fd(args[i], STDOUT_FILENO);
			if (args[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		ft_putstr_fd(&backline, STDOUT_FILENO);
	}
}
