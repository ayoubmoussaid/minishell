/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/01/04 09:21:47 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

char	*g_builtins[] = {"echo", "pwd", "cd", "env", "export", "unset", "exit", (void*)0};

t_cmd *create_one(char *c, char *args[], t_files *files)
{
	t_cmd	*cmd;
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->c = c;
	cmd->args = args;
	cmd->files = files;
	cmd->next = NULL;
	return (cmd);
}


t_pipeline	*create_fake_cmd()
{
	t_pipeline *pipeline;
	pipeline = (t_pipeline*)malloc((sizeof(t_pipeline)));
	char *tab[] = {"-la", (char*)0};
	pipeline->pipe = create_one("ls", tab, NULL);
	pipeline->next = NULL;
	// char *tab1[] = {"-e", (char*)0};
	// pipeline->pipe->next = create_one("cat", tab1, NULL);
	// char *tab2[] = {"$PATH", "hello", (char*)0};
	// pipeline->next = (t_pipeline*)malloc((sizeof(t_pipeline)));
	// pipeline->next->pipe = create_one("echo", tab2, NULL);
	// pipeline->next->next = NULL;
	return (pipeline);
}

void	prepare_fd(t_shell *shell, t_cmd *cmd, int p[2])
{
	t_files *file;

	file = cmd->files;
	p[0] = -1;
	p[1] = -1;
	if(!file && cmd->next)
	{
		fprintf(shell->debug_file, "i got here \n");
		pipe(p);
		dup2(p[0], STDIN_FILENO);
		dup2(p[1], STDOUT_FILENO);
	}
	while(file)
	{
		fprintf(shell->debug_file, "name: %s\n", file->name);
		if(file->type == '>' || file->type == 'a')
		{
			if(p[STDOUT_FILENO] != -1)
				close(p[STDOUT_FILENO]);
			p[STDOUT_FILENO] = open(file->name, O_CREAT | (file->type == '>' ? O_WRONLY : O_APPEND));
			if(p[STDOUT_FILENO] == -1)
			{
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				exit(0);
			}	
		}
		else
		{
			if(p[STDIN_FILENO] != -1)
				close(p[STDIN_FILENO]);
			p[STDIN_FILENO] = open(file->name, O_RDONLY);
			if(p[STDIN_FILENO] == -1)
			{
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
				exit(0);
			}
		}
		file = file->next;
	}
	//TODO dupliacte fd .. you forgot it
}

int		check_for_slash(char *str)
{
	int i;

	i = -1;
	while (str && str[++i] != '\0')
		if (str[i] == '/')
			return (1);
	return (0);	
}

int		check_builtins(char *str)
{
	int i;

	i = -1;
	while(g_builtins[++i])
		if(ft_strcmp(g_builtins[i], str) == 0)
			return (i);
	return (-1);
}

char	*get_path(t_shell *shell, t_cmd	*cmd)
{
	char			*path;
	char			**all_paths;
	int				i;
	DIR				*dfd;
	struct dirent	*dp;
	struct stat		stbuf;

	i = -1;
	path = get_env_var(shell, "PATH");
	all_paths = ft_split(path, ':');
	while (all_paths[++i] != 0)
	{
		//fprintf(shell->debug_file, "************ %s ************\n", all_paths[i]);
		if ((dfd = opendir(all_paths[i])) == NULL)
			continue;
		while ((dp = readdir(dfd)) != NULL)
		{
			path = ft_specialjoin(all_paths[i], dp->d_name, '/');
			ft_putendl_fd(path, 1);
			if (stat(path, &stbuf) == -1){
				//ft_putendl_fd(strerror(errno), STDERR_FILENO);
				continue;
			}
			if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
				continue;
			fprintf(shell->debug_file, "*** %s ***\n", dp->d_name);
			if(ft_strcmp(dp->d_name, cmd->c) == 0)
				return (path);
		}
		closedir(dfd);
	}
	return "hi";
}

int 	get_real_cmd(t_shell *shell, t_cmd *cmd)
{
	int		index;

	index = -1;
	
	if(check_for_slash(cmd->c) || (index = check_builtins(cmd->c)) != -1)
		cmd->executable = cmd->c;
	else
		cmd->executable = get_path(shell, cmd);
	return (index);
}

void	execute_builtin(t_shell *shell, t_cmd *cmd, int index)
{
	static void (*builtin_functions[7])(t_shell *shell, t_cmd *cmd) = {ft_echo, ft_pwd, ft_cd, ft_env, ft_export, ft_unset, ft_exit};
	builtin_functions[index](shell, cmd);
}

void	execute_non_builtin(t_shell *shell, t_cmd *cmd)
{
		pid_t pid = fork();
		if(pid == 0)
		{
			int x = execve(cmd->executable, cmd->args, NULL);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(x);
		}
		else if (pid > 0)
		{
			int status;
			fprintf(shell->debug_file, "parent process here\n");
			waitpid(pid, &status, 0);
			fprintf(shell->debug_file, "child process exited %d | %d --- status:%d\n", pid, getpid(), status);
		}
}

void	execute(t_shell *shell)
{
	t_pipeline	*pipeline;
	t_cmd		*cmd;
	int p[2];
	int std[2];
	int index;

	pipeline = shell->pipeline;
	std[STDIN_FILENO] = dup(STDIN_FILENO);
	std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while(pipeline)
	{
		cmd = pipeline->pipe;
		fprintf(shell->debug_file, "------------------------------\n");
		while(cmd)
		{
			fprintf(shell->debug_file, "-- %s --\n", cmd->c);
			prepare_fd(shell, cmd, p);
			if ((index = get_real_cmd(shell, cmd)) != -1)
				execute_builtin(shell, cmd, index);
			else
			{
				/* code */
			}
			
			//TODO execute
			cmd = cmd->next;
			dup2(std[STDIN_FILENO], STDIN_FILENO);
			dup2(std[STDOUT_FILENO], STDOUT_FILENO);
		}

		pipeline = pipeline->next;
	}
}


int     main(int argc, char **argv, char **env)
{
	
	t_shell *shell;

	shell = (t_shell*)malloc(sizeof(t_shell));
	shell->envs = NULL;
	shell->pipeline = create_fake_cmd();
	//write(1, "\n=============================\n", 31);
	shell->debug_file = fopen("debug.txt", "w");
	if (argc > 1)
		argv = NULL;
	my_env(env, shell);
	//print_env(shell);
	execute(shell);
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


