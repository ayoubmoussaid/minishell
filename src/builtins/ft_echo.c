/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:24:53 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/07 14:00:07 by amoussai         ###   ########.fr       */
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
	printf("len: %d\n", len);
	while (shell->env[i] != NULL)
	{
		//TODO fix this .. there is a segmentation fault
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		tofree = ft_substr(shell->env[i], 0, len);
		//ft_putendl_fd(tofree, STDOUT_FILENO);
		//ft_putendl_fd("\n", STDOUT_FILENO);
		if (ft_strcmp(tofree, search) == 0)
		{
			write(1, "hi\n", 3);
			return (ft_substr(shell->env[i], len, ft_strlen(shell->env[i])));
		}
		free(tofree);
		i++;
	}
	return (ft_strdup("\n"));
}

void	ft_echo(t_shell *shell, char **args)
{
	int		i;
	char	backline;
	char	*str;

	backline = '\n';
	i = -1;
	shell = NULL;
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
				ft_putstr_fd("str\n", STDOUT_FILENO);
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
