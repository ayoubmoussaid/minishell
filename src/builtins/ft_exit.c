/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 10:41:49 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/04 15:13:12 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
**	//TODO fix exit, later though
*/

void	to_exit(int value)
{
	ft_putendl_fd("exit", 1);
	exit(value);
}

int	ft_exit(t_cmd *cmd)
{
	int		index;

	index = 0;
	if (ft_len(cmd->args) > 2)
	{
		error_handle(E_TMA, 1, cmd->c);
		to_exit(255);
	}
	while (cmd->args[1] && cmd->args[1][index])
		if (!ft_isdigit(cmd->args[1][index++]))
		{
			error_handle(E_EXIT_ARG, 2, cmd->args[1]);
			to_exit(255);
		}
	cmd->args[1] == NULL ? to_exit(0) : to_exit(ft_atoi(cmd->args[1]));
	return (0);
}
