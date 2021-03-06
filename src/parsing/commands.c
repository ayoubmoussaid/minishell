/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:48:59 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 15:27:53 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	add_cmd_to_list(t_cmd *cmd)
{
	t_cmd *current;

	cmd->next = NULL;
	current = g_shell->cmd;
	if (current == NULL)
	{
		g_shell->cmd = cmd;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = cmd;
	}
}

void	ft_to_pos(char **s)
{
	int i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] < 0)
			(*s)[i] = -(*s)[i];
		i++;
	}
	if (ft_strcmp(*s, "\"\"") == 0 || ft_strcmp(*s, "\'\'") == 0)
	{
		free(*s);
		*s = ft_strdup("");
	}
}

void	ft_fix_neg_cmd(t_cmd *cmd)
{
	t_files *file;
	int		i;

	i = -1;
	file = cmd->files;
	while (file)
	{
		ft_to_pos(&(file->name));
		file = file->next;
	}
	while (cmd->args[++i])
		ft_to_pos(&(cmd->args[i]));
}

void	fill_cmd(t_getl *g_getl, int i)
{
	t_cmd	*cmd;
	int		index;

	index = -1;
	g_getl->sp_p = ft_split(g_getl->sp_c[i], '|');
	while (g_getl->sp_p[++index])
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmd->files = NULL;
		cmd->next = NULL;
		ft_find_file(&g_getl->sp_p[index], cmd);
		cmd->args = ft_split(g_getl->sp_p[index], ' ');
		ft_fix_neg_cmd(cmd);
		cmd->c = cmd->args[0];
		add_cmd_to_list(cmd);
	}
	ft_free(g_getl->sp_p);
}

void	get_command(t_getl *g_getl)
{
	int i;

	i = -1;
	g_getl->sp_c = ft_split(g_getl->line, ';');
	while (g_getl->sp_c[++i])
	{
		g_shell->cmd = NULL;
		flip_line(&(g_getl->sp_c[i]));
		fill_cmd(g_getl, i);
		execute();
		ft_clear_cmd_list();
		g_pid = 0;
	}
	ft_free(g_getl->sp_c);
}
