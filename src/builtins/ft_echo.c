/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:24:53 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/07 10:02:32 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_echo(t_shell *shell, char **args)
{
	int		i;
	char	backline;

	backline = '\0';
	i = -1;
	shell = NULL;
	if (!args)
		ft_putendl_fd("", STDOUT_FILENO);
	else
	{
		if (ft_strcmp(args[0], "-n") == 0)
		{
			args++;
			backline = '\n';
		}
		while (args[++i] != NULL)
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
			if (args[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		ft_putstr_fd(&backline, STDOUT_FILENO);
	}
}
