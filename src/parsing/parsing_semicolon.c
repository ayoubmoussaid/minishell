/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_semicolon.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:35:06 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 19:03:29 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_s_semicolon(t_getl *g_getl, int *i)
{
	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
	else if (is_all_off(g_getl) || !g_getl->i)
	{
		if (g_getl->line[*i - 1] == ';'
		|| (g_getl->line[*i + 1] && g_getl->line[*i + 1] == ';'))
			error_handle(E_SYNTAX, 258, g_mishell_err[COMMAD]);
		else
			error_handle(E_SYNTAX, 258, g_mishell_err[COMMA]);
		return (1);
	}
	else
		g_getl->semicolon = 1;
	return (0);
}
