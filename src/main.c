/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/28 15:08:21 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

char	*g_builtins[] = {"echo", "pwd", "env", "export", "unset", "exit"};

t_cmd *create_one(char *c, char *args[], int pipe, int prepipe, t_files *files)
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
	char *tab[] = {"-la", (char*)0};
	cmd = create_one("ls", tab, 1, 0, NULL);
	char *tab1[] = {"-e", (char*)0};
	cmd->next = create_one("cat", tab1, 0, 1, NULL);
	char *tab2[] = {"$PATH", "hello", (char*)0};
	cmd->next->next = create_one("echo", tab2, 0, 0, NULL);
	return (cmd);
}

void	prepare_fd(t_cmd *cmd/* , int p[2], int std[2] */)
{
	int write, read;

	write = 1;
	read = 1;
	if(cmd->files)
	{
		//make a traversal on files;
		read = 0;
		write = 0;
	}	
	if(write && cmd->pipe)
	{
		//open pipe for read;
	}
	if(read && cmd->prepipe)
	{
		//read from pipe already openned
	}

}

void	execute(t_shell *shell)
{
	t_cmd *cur;
	
	cur = shell->cmd;
	// int p[2];
	// int std[2];
	while(cur != NULL)
	{
		prepare_fd(cur/* , p, std */);
		

		cur = cur->next;
	}
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
	print_env(shell);
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


