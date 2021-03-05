/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/05 19:05:59 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main(int argc, char **argv, char **env)
{

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	
	if (argc > 1)
		argv = NULL;
	do_the_work(env);
	g_shell->exit_status = 0;
	g_getl = (t_getl *)malloc(sizeof(t_getl));
	g_shell->cmd = NULL;
	parse_line(g_getl);
	return (0);
}
