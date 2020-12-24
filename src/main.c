/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/24 12:31:05 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

t_cmd *create_one(char *c, char **args, int pipe, int prepipe, t_files *files)
{
	t_cmd	*cmd;
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->c = c;
	cmd->args = args;
	cmd->pipe = pipe;
	cmd->prepipe = prepipe;
	cmd->files = files;
	cmd->next = NULL;
	return (cmd);
}


t_cmd	*create_fake_cmd()
{
	t_cmd *cmd;
	cmd = create_one("ls", (char**){"-la", NULL}, 1, 0, NULL);
	cmd->next = create_one("cat", (char**){"-e", NULL}, 0, 1, NULL);
	cmd->next->next = create_one("echo", (char**){"$PATH", "hello", NULL}, 0, 0, NULL);
	return (cmd);
}


int     main(int argc, char **argv, char **env)
{
	
	t_shell *shell;

	shell = (t_shell*)malloc(sizeof(t_shell));
	shell->envs = NULL;
	shell->cmd = create_fake_cmd();
	//write(1, "\n=============================\n", 31);
	shell->debug_file = fopen("debug.txt", "w");
	if (argc > 1)
		argv = NULL;
	my_env(env, shell);
	//print_env(shell);
	//ft_env(shell->envs);
	//ft_pwd();
	//ft_cd(shell, "..");
	//ft_cd(shell, "minishell");
	//ft_cd(shell, "/freak");

	// tab is a simple table containing args for test
	// char *tab[] = {"abc=b", "avc=ff", "abc=d=5", "=a%ef", (void*)0};
	// ft_export(shell, tab);
	// print_env(shell);
	// write(1, "=============================\n", 30);
	// ft_env(shell->env);
	// write(1, "=============================\n", 30);
	//char *test[] = {"abc", "ef&fe", (void*)0};
	//ft_unset(shell, test);
	//print_env(shell);
	// fprintf(shell->debug_file, "=============================\n");
	// write(1, "=============================\n", 30);

	// char *test[] = {"$abc", "$PATH", "$%dwa=", "$awd", "drgdrgdrg", (void*)0};
	// ft_echo(shell, test);
	 
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


