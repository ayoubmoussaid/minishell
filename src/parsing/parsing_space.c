/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:37:57 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 19:03:50 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	verify_space(t_getl *g_getl, int *i)
{
	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
}
