/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:37:07 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 19:00:02 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	verify_rest(t_getl *g_getl, int *i)
{
	if (g_getl->semicolon && !is_special_char(g_getl->line[*i])
	&& g_getl->line[*i] != ' ')
		g_getl->semicolon = 0;
	else if (g_getl->pipe && !is_special_char(g_getl->line[*i]))
		g_getl->pipe = 0;
	else if (g_getl->red_in && !is_special_char(g_getl->line[*i]))
		g_getl->red_in = 0;
	else if (g_getl->append && !is_special_char(g_getl->line[*i]))
		g_getl->append = 0;
	else if (g_getl->red_out && !is_special_char(g_getl->line[*i]))
		g_getl->red_out = 0;
}
