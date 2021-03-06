/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:28:50 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 17:13:29 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		parse_files(t_cmd *cmd)
{
	t_files	*iterator;
	int		no_error;

	cmd->fdr = -2;
	cmd->fdw = -2;
	iterator = cmd->files;
	no_error = 1;
	while (iterator && no_error)
	{
		if (iterator->type == 'a' || iterator->type == '>')
		{
			(cmd->fdw != -2) ? close(cmd->fdw) : 1;
			if ((cmd->fdw = open(iterator->name, O_WRONLY | O_CREAT |
				(iterator->type == '>' ? O_TRUNC : O_APPEND), 0644)) < 0)
				no_error = 0;
		}
		else
		{
			(cmd->fdr != -2) ? close(cmd->fdr) : 1;
			if ((cmd->fdr = open(iterator->name, O_RDONLY)) < 0)
				no_error = 0;
		}
		iterator = no_error ? iterator->next : iterator;
	}
	if (!no_error)
		error_handle(E_STANDARD, 1, iterator->name);
	return (no_error);
}

void	dup_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error_handle(E_STANDARD, 1, NULL);
	close(fd1);
}

int		prepare_fd(t_cmd *cmd, int *p, int *std)
{
	int check;

	check = parse_files(cmd);
	if (cmd->next && pipe(p) == 0)
		dup_close(p[WRITE], STDOUT_FILENO);
	if (cmd->next == NULL)
		dup2(std[STDOUT_FILENO], STDOUT_FILENO);
	if (cmd->files && cmd->fdw > 0)
		dup_close(cmd->fdw, STDOUT_FILENO);
	if (cmd->files && cmd->fdr > 0)
		dup_close(cmd->fdr, STDIN_FILENO);
	return (check);
}

void	finish_fd(t_cmd *cmd, int *p, int *std)
{
	if (cmd->next)
		dup_close(p[READ], STDIN_FILENO);
	else
	{
		dup2(std[STDIN_FILENO], STDIN_FILENO);
		dup2(std[STDOUT_FILENO], STDOUT_FILENO);
	}
}
