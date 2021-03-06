/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 19:52:07 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	check_line(t_getl *g_getl)
{
	while (g_getl->line[++(g_getl->i)] && !g_getl->brake)
	{
		if (g_getl->line[g_getl->i] == (char)39)
			verify_s_quote(g_getl);
		else if (g_getl->line[g_getl->i] == (char)34)
			verify_d_quote(g_getl);
		else if (g_getl->line[g_getl->i] == ' ')
			verify_space(g_getl, &g_getl->i);
		else if (g_getl->line[g_getl->i] == ';' || g_getl->line[g_getl->i] ==
		'|' || g_getl->line[g_getl->i] == '>' || g_getl->line[g_getl->i] ==
		'<')
		{
			if (((g_getl->line[g_getl->i] == ';' && verify_s_semicolon(g_getl,
			&g_getl->i)) || (g_getl->line[g_getl->i] == '|' && verify_s_pipe(
			g_getl, &g_getl->i)) || (g_getl->line[g_getl->i] == '>' &&
			verify_s_red(g_getl, &g_getl->i)) || (g_getl->line[g_getl->i] ==
			'<' && verify_s_red_out(g_getl, &g_getl->i))))
				g_getl->brake = 1;
		}
		else
			verify_rest(g_getl, &g_getl->i);
	}
}

int		get_line_error(int ret)
{
	int	var;

	var = 1;
	if (ret == -1)
	{
		error_handle(E_STANDARD, errno, "");
		var = 0;
	}
	else if (ft_strlen(g_getl->line) == 0 && ret == 0)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	return (var);
}

void	parse_line(t_getl *g_getl)
{
	int ret;

	while (1)
	{
		g_shell->exit_status == 0 ?
		ft_putstr_fd("\033[92mminishell$> \033[39m", STDOUT_FILENO)
		: ft_putstr_fd("\033[91mminishell$> \033[39m", STDOUT_FILENO);
		g_getl->line = NULL;
		ret = get_next_line(0, &g_getl->line);
		if (get_line_error(ret))
		{
			init_state(g_getl);
			g_getl->i = -1;
			check_line(g_getl);
			if ((!g_getl->brake && verify_final(g_getl))
			|| (g_getl->brake == 1))
			{
				free(g_getl->line);
				continue;
			}
			else
				get_command(g_getl);
		}
		free(g_getl->line);
	}
}
