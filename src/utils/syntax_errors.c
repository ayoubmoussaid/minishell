/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 09:20:42 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"



void	init_state(t_getl *g_getl)
{
	g_getl->s_quote = 0;
	g_getl->d_quote = 0;
	g_getl->dollar = 0;
	g_getl->semicolon = 0;
	g_getl->red_in = 0;
	g_getl->append = 0;
	g_getl->append = 0;
	g_getl->pipe = 0;
	g_getl->brake = 0;
	g_getl->red_out = 0;
}

int is_special_char(char c)
{
	return (c == ';' || c == '|' || c == ' ');
}

int is_all_off(t_getl *g_getl)
{
	return (g_getl->pipe || g_getl->semicolon ||  g_getl->red_in || g_getl->append || g_getl->red_out);
}

int is_on(t_getl *g_getl)
{
	int is_on;

	is_on = 0;
	if (g_getl->semicolon)
		is_on = 1;
	else if (g_getl->pipe)
		is_on = 2;
	else if (g_getl->red_in)
		is_on = 3;
	else if (g_getl->append)
		is_on = 4;
	else if (g_getl->red_out)
		is_on = 5;
	return (is_on);// 0
}
