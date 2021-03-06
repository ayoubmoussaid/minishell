/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_s_d_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:32:09 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 19:02:37 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	verify_s_quote(t_getl *g_getl)
{
	if (quote_handler(g_getl, '\'') || g_getl->d_quote)
		return ;
	g_getl->s_quote = !(g_getl->s_quote);
}

int		verify_d_quote(t_getl *g_getl)
{
	if (quote_handler(g_getl, '\"'))
		return (g_getl->d_quote);
	if (g_getl->s_quote == 1
	|| (g_getl->d_quote && g_getl->line[g_getl->i - 1] == '\\'))
		return (g_getl->d_quote);
	else if (!g_getl->d_quote)
	{
		g_getl->semicolon = 0;
		g_getl->pipe = 0;
		g_getl->red_in = 0;
		g_getl->append = 0;
		g_getl->d_quote = 1;
	}
	else
		g_getl->d_quote = 0;
	return (g_getl->d_quote);
}

int		quote_handler(t_getl *g_getl, char c)
{
	if (g_getl->line[g_getl->i] == c
	&& g_getl->line[g_getl->i + 1] == c)
	{
		if ((g_getl->i == 0 ||
		(g_getl->line[g_getl->i - 1] && g_getl->line[g_getl->i - 1] == ' '))
		&& ((g_getl->line[g_getl->i + 2] && g_getl->line[g_getl->i + 2] == ' ')
		|| g_getl->line[g_getl->i + 2] == '\0'))
		{
			g_getl->line[g_getl->i] = -g_getl->line[g_getl->i];
			g_getl->line[g_getl->i + 1] = -g_getl->line[g_getl->i + 1];
			return (1);
		}
	}
	return (0);
}
