/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 10:41:49 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/02 11:46:15 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
**	//TODO fix exit, later though
*/

int	ft_exit(t_cmd *cmd)
{
	if (cmd)
		exit(0);
	else
		exit(0);
	return (1);
}
