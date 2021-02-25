/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/25 14:33:25 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int main(int argc, char **argv, char **env)
{

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	t_getl *getl;
	if (argc > 1)
		argv = NULL;
	do_the_work(env);
	g_shell->exit_status = 0;
	getl = (t_getl *)malloc(sizeof(t_getl));
	g_shell->cmd = NULL;
	parse_line(getl);
	// while(1)
	// {
	// 	ft_putstr_fd("minishell $> ", STDOUT_FILENO);
	// 	get_next_line(STDIN_FILENO, &(g_shell->line));
	// 	//g_shell->line = ft_strdup("hello \"$\"PWD");
	// 	ft_putendl_fd(g_shell->line, STDOUT_FILENO);
	// 	flip_line();
	// 	//check_line();
	// 	ft_putendl_fd(reflip(g_shell->line), STDOUT_FILENO);
	// 	free(g_shell->line);
	// }
	// fclose(g_shell->debug_file);
	return (0);
}
