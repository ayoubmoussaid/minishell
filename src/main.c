/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 18:15:45 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void	do_the_work(char **env)
{
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	g_shell->envs = NULL;
	my_env(env);
}

int		main(int argc, char **argv, char **env)
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
