/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:16:29 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 15:22:41 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_clear_files_list(t_cmd *cmd)
{
	t_files *current;
	t_files *next;

	current = cmd->files;
	next = NULL;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = NULL;
		current = next;
	}
	cmd->files = NULL;
}

void	ft_clear_cmd_list(void)
{
	t_cmd *current;
	t_cmd *next;

	current = g_shell->cmd;
	next = NULL;
	while (current)
	{
		next = current->next;
		free(current->executable);
		ft_clear_files_list(current);
		ft_free(current->args);
		current->args = NULL;
		current->executable = NULL;
		free(current);
		current = next;
	}
}
