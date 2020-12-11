/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/11 10:20:07 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void	fct(int num)
{
	printf("processus fils est terminé ! , %d.\n", num);
}


void	my_env(char **env, t_shell *shell)
{
	int i;
	int j;

	i = 0;
	while (env[i] != NULL)
		i++;
	shell->env = (char**)malloc(sizeof(char*) * (i + 1));
	
	j = 0;
	while (j < i)
	{
		shell->env[j] = ft_strdup(env[j]);
		j++;
	}
	shell->env[j] = NULL;
}


int     main(int argc, char **argv, char **env)
{
	//TODO export b="\""
	//TODO echo "\$PWD"
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
	char *tab[] = {"x=5", "f=sef", "%dwa=", "awd", "_awd", (void*)0};
	ft_export(shell, tab);

	//ft_env(shell->env);
	//write(1, "=============================\n", 30);
	
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






/* int     ft_len(char **tab){
	int i;

	i=0;
	while(tab[i] != NULL){
		i++;
	}
	return i;
}

int ft_verify(char *str){
	int i;

	i = 0;
	while (str[i] != '\0'){
		if (str[i] == ';' && str[i + 1] == ';'){
			return (0);
		}
	}
	return (1);
}

void    parse_line(char *str){
	
	char **str_table = ft_split(str, ';');
	printf("\nlen: %d\n", ft_len(str_table));
	int i = 0;
	while(str_table[i] != NULL){
		printf("-- %s --\n", str_table[i]);
		i++;
	}
}

void    read_line(){
	char    *line;
	int     ret = 0;
	ft_putstr_fd("\x1B[92m->minishell=> \x1B[39m", STDOUT_FILENO);
	while((ret = get_next_line(STDIN_FILENO, &line)) != -1){
		ft_putstr_fd(line, STDOUT_FILENO);
		parse_line(line);
		free(line);
		ft_putstr_fd("\x1B[92m\n-> minishell=> \x1B[39m", STDOUT_FILENO);
	}
} */
