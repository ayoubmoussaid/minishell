/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:36:03 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 18:57:21 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_s_pipe(t_getl *g_getl, int *i)
{
	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
	else if (is_all_off(g_getl) || !g_getl->i)
	{
		error_handle(E_SYNTAX, 258, g_mishell_err[PIPE]);
		return (1);
	}
	else
		g_getl->pipe = 1;
	return (0);
}
