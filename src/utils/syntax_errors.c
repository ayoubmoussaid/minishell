/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/02 18:04:10 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	errrors(char *err)
{
	ft_putendl_fd(err, 1);
}

void	init_state(t_getl *getl)
{
	getl->s_quote = 0;
	getl->d_quote = 0;
	getl->dollar = 0;
	getl->semicolon = 0;
	getl->red_in = 0;
	getl->append = 0;
	getl->append = 0;
	getl->pipe = 0;
	getl->brake = 0;
	getl->red_out = 0;
}

int is_special_char(char c)
{
	return (c == ';' || c == '|' || c == ' ');
}

int is_all_off(t_getl *getl)
{
	return (getl->pipe || getl->semicolon ||  getl->red_in || getl->append || getl->red_out);
}

int is_on(t_getl *getl)
{
	int is_on;

	is_on = 0;
	if (getl->semicolon)
		is_on = 1;
	else if (getl->pipe)
		is_on = 2;
	else if (getl->red_in)
		is_on = 3;
	else if (getl->append)
		is_on = 4;
	else if (getl->red_out)
		is_on = 5;
	return (is_on);// 0
}