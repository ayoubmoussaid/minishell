/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_red_in_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:57:52 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 18:58:44 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_s_red(t_getl *g_getl, int *i)
{
	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
	else if (g_getl->line[*i + 1] && g_getl->line[*i + 1] == '>')
	{
		if (g_getl->red_in || g_getl->red_out || g_getl->append)
		{
			error_handle(E_SYNTAX, 258, g_mishell_err[INFILED]);
			return (1);
		}
		g_getl->append = 1;
		g_getl->i += 1;
	}
	else
	{
		if (g_getl->red_in || g_getl->red_out || g_getl->append)
		{
			error_handle(E_SYNTAX, 258, g_mishell_err[INFILE]);
			return (1);
		}
		g_getl->red_in = 1;
	}
	g_getl->semicolon = 0;
	g_getl->pipe = 0;
	return (0);
}

int	verify_s_red_out(t_getl *g_getl, int *i)
{
	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
	else
	{
		if (g_getl->red_in || g_getl->red_out || g_getl->append)
		{
			error_handle(E_SYNTAX, 258, g_mishell_err[OUTFILE]);
			return (1);
		}
		g_getl->red_out = 1;
		g_getl->semicolon = 0;
		g_getl->pipe = 0;
	}
	return (0);
}
