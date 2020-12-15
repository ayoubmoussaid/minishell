/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/15 10:18:50 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void	fct(int num)
{
	printf("processus fils est terminé ! , %d.\n", num);
}


void	my_env(char **env, t_shell *shell)
{
	int len;
	int j;

	len = ft_len(env);
	shell->env = (char**)malloc(sizeof(char*) * (len + 1));
	
	j = 0;
	while (j < len)
	{
		shell->env[j] = ft_strdup(env[j]);
		j++;
	}
	shell->env[j] = NULL;
}


int     main(int argc, char **argv, char **env)
{
	
	t_shell *shell;

	shell = (t_shell*)malloc(sizeof(t_shell));
	//write(1, "\n=============================\n", 31);
	shell->debug_file = fopen("debug.txt", "w");
	if (argc > 1)
		argv = NULL;
	my_env(env, shell);
	//ft_env(shell.env);
	//ft_pwd();
	//ft_cd(&shell, "..");
	//ft_cd(&shell, "minishell");
	//ft_cd(&shell, "/freak");

	//tab is a simple table containing args for test
	char *tab[] = {"abc=b", "avc=ff", (void*)0};
	ft_export(shell, tab);
	write(1, "=============================\n", 30);
	ft_env(shell->env);
	write(1, "=============================\n", 30);
	char *test[] = {"abc", "avc", "ef=fe", (void*)0};
	ft_unset(shell, test);
	ft_env(shell->env);
	write(1, "=============================\n", 30);

	//char *test[] = {"$x", "$f", "$%dwa=", "$awd", "$_awd", (void*)0};
	//ft_echo(shell, test);
	
/* 	pid_t pid = fork();
	if(pid == 0)
	{
		char *args[] = {"/bin/ls", "$l",(char *)0};
		char *env_args[] = {"l=-la",(char*)0};
		printf("salut from child\n");
		int x = execve(args[0], args, env_args);
		printf("child says: %d\n", x);
		sleep(2);
		exit(0);
	}
	else if (pid > 0)
	{
		int status;
		printf("parent process here\n");
		waitpid(pid, &status, 0);
		printf("child process exited %d | %d\n", pid, getpid());	
	}
	else
	{
		printf("some error occured!\n");
	}  */

	//pause();
	fclose(shell->debug_file);
	return (0);
}


