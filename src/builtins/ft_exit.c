/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 10:41:49 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/07 09:38:27 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		ft_exit(t_cmd *cmd)
{
	long long		index;

	write(2, "exit\n", 5);
	cmd->args[1] == NULL ? exit(0) : 1;
	index = (cmd->args[1][0] == '-') || (cmd->args[1][0] == '+') ? 1 : 0;
	while (cmd->args[1] && cmd->args[1][index])
		if (!ft_isdigit(cmd->args[1][index++]))
			exit(error_handle(E_EXIT_ARG, 255, cmd->args[1]));
	if (ft_len(cmd->args) > 2)
		return (error_handle(E_TMA, 1, cmd->executable));
	index = ft_atoi(cmd->args[1]);
	if (cmd->args[1] && ((index < 0 && cmd->args[1][0] != '-')
	|| (index >= 0 && cmd->args[1][0] == '-')))
		error_handle(E_EXIT_ARG, 2, cmd->args[1]);
	exit(index);
	return (0);
}
