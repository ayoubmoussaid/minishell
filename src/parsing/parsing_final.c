/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_final.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:38:41 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 18:56:51 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_final(t_getl *g_getl)
{
	int err;

	if (g_getl->s_quote || g_getl->d_quote)
	{
		err = (g_getl->s_quote) ? QUOTES : QUOTED;
		error_handle(E_SYNTAX, 258, g_mishell_err[err]);
		return (1);
	}
	else if ((err = is_on(g_getl)) > 1)
	{
		if (err == 2)
			error_handle(E_SYNTAX, 258, g_mishell_err[PIPE]);
		else if (err == 3 || err == 4 || err == 5)
			error_handle(E_SYNTAX, 258, g_mishell_err[RED]);
		return (1);
	}
	return (0);
}
