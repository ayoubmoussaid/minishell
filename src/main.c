/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/21 10:50:08 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int		ft_str_index(char *str, char c)
{
	int i = 0;
	while(str && str[i] != '\0')
	{
		if(str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	my_env(char **env, t_shell *shell)
{
	int		j;
	t_env	*elt;
	char	*key;
	char	*value;
	int		index;

	j = 0;
	while (env[j] != NULL)
	{
		if((index = ft_str_index(env[j], '=')) != -1)
		{
			key = ft_substr(env[j], 0, index);
			value = ft_substr(env[j], index + 1, ft_strlen(env[j]));
			elt = create_new_var(key, value);
			add_env_var(shell, elt);
			free(key);
			free(value);
		}
		j++;
	}
}


int     main(int argc, char **argv, char **env)
{
	
	t_shell *shell;

	shell = (t_shell*)malloc(sizeof(t_shell));
	*(shell->envs) = NULL;
	//write(1, "\n=============================\n", 31);
	shell->debug_file = fopen("debug.txt", "w");
	if (argc > 1)
		argv = NULL;
	my_env(env, shell);
	//print_env(shell);
	//ft_env(shell.env);
	//ft_pwd();
	//ft_cd(shell, "..");
	//ft_cd(shell, "minishell");
	//ft_cd(shell, "/freak");

	//tab is a simple table containing args for test
	char *tab[] = {"abc=b", "avc=ff", (void*)0};
	ft_export(shell, tab);
	print_env(shell);
	// write(1, "=============================\n", 30);
	// ft_env(shell->env);
	// write(1, "=============================\n", 30);
	// char *test[] = {"abc", "avc", "ef=fe", (void*)0};
	// ft_unset(shell, test);
	// ft_env(shell->env);
	// write(1, "=============================\n", 30);

	//char *test[] = {"$x", "$PATH", "$%dwa=", "$awd", "$_awd", (void*)0};
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


