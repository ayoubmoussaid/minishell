/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:13:45 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 18:14:01 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT && g_pid == 0)
	{
		ft_putstr_fd("\b\b  \b\b\033[91m\nminishell$> \033[39m", 1);
		if (ft_strlen(g_getl->line) == 0)
			g_shell->exit_status = 1;
		else
			g_shell->exit_status = 128 + sig;
	}
	if (sig == SIGQUIT)
	{
		if (g_pid == 0)
			write(1, "\b \b\b \b", 6);
	}
}
