/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 10:41:49 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/20 16:21:16 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
**	//TODO fix exit, later though
*/

int	ft_exit(t_cmd *cmd)
{
	int		index;

	index = 0;
	if (ft_len(cmd->args) > 2)
		return (error_handle(E_TMA, 1, cmd->c));
	while (cmd->args[1] && cmd->args[1][index])
		if (!ft_isdigit(cmd->args[1][index++]))
			return (error_handle(E_EXIT_ARG, 2, cmd->args[1]));
	cmd->args[1] == NULL ? exit(0) : exit(ft_atoi(cmd->args[1]));
	return (0);
}
