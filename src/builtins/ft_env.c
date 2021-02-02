/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:12 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/02 11:46:40 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_env(t_cmd *cmd)
{
	t_env *current;

	if (cmd->args){}
	current = g_shell->envs;
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		current = current->next;
	}
	return 1;
}
