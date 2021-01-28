/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/01/28 17:57:25 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

char	*g_builtins[] = {"echo", "pwd", "cd", "env", "export", "unset", "exit", (void*)0};

t_cmd *create_one(char *c, char **args, t_files *files)
{
	t_cmd	*cmd;
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->c = c;
	cmd->args = args;
	cmd->files = files;
	cmd->next = NULL;
	return (cmd);
}

t_files *get_one_file(){
	t_files *file = (t_files*)malloc(sizeof(t_files));
	file->name = ft_strdup("testing");
	file->type = '<';
	file->next =(t_files*)malloc(sizeof(t_files)); 
	file->next->name = ft_strdup("testing1");
	file->next->type = '<';
	file->next->next =(t_files*)malloc(sizeof(t_files)); 
	file->next->next->name = ft_strdup("testing2");
	file->next->next->type = '<';
	file->next->next->next = NULL;
	return file;
}

t_pipeline	*create_fake_cmd()
{
	t_pipeline *pipeline;
	pipeline = (t_pipeline*)malloc((sizeof(t_pipeline)));
	char **tab = (char**)malloc(sizeof(char*)*3);
	tab[0] = ft_strdup("ls");
	tab[1] = ft_strdup("-la");
	tab[2] = NULL;
	pipeline->pipe = create_one(tab[0], tab, NULL);
	char **tab1 = (char**)malloc(sizeof(char*)*3);
	tab1[0] = ft_strdup("cat");
	tab1[1] = ft_strdup("-e");
	tab1[2] = NULL;
	pipeline->pipe->next = create_one(tab1[0], tab1, get_one_file());
	// char **tab2 = (char**)malloc(sizeof(char*)*3);
	// tab2[0] = ft_strdup("grep");
	// tab2[1] = ft_strdup("l");
	// tab2[2] = NULL;
	// pipeline->pipe->next->next = create_one(tab2[0], tab2, NULL);
	// char **tab3 = (char**)malloc(sizeof(char*)*3);
	// tab3[0] = ft_strdup("cat");
	// tab3[1] = ft_strdup("-e");
	// tab3[2] = NULL;
	// pipeline->pipe->next->next->next = create_one(tab3[0], tab3, NULL);
	pipeline->next = NULL;
	return (pipeline);
}

int parse_files(t_cmd *cmd)
{
	t_files *iterator;

	cmd->fdr = -2;
	cmd->fdw = -2;
	iterator = cmd->files;
	int no_error = 1;
	while(iterator && no_error)
	{
		if (iterator->type == 'a' || iterator->type == '>')
		{
			close(cmd->fdw);
			if((cmd->fdw = open(iterator->name, O_WRONLY | O_CREAT | (iterator->type == '>' ? O_TRUNC : O_APPEND), 0644)) < 0)
				no_error = 0;
		}
		else
		{
			close(cmd->fdr);
			if((cmd->fdr = open(iterator->name, O_RDONLY)) < 0)
				no_error = 0;
		}
		iterator = iterator->next;
	}
	if(!no_error){
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	prepare_fd(t_cmd *cmd, int p[2], int std[2])
{
	int check = parse_files(cmd);
	if(cmd->next && pipe(p) == 0)
	{
		dup2(p[WRITE], STDOUT_FILENO);
		close(p[WRITE]);
	}
	if(cmd->next == NULL)
		dup2(std[WRITE], STDOUT_FILENO);
	if(cmd->files && cmd->fdw > 0)
	{
		dup2(cmd->fdw, STDOUT_FILENO);
		close(cmd->fdw);
	}
	if(cmd->files && cmd->fdr > 0)
	{
		dup2(cmd->fdr, STDIN_FILENO);
		close(cmd->fdr);
	}
	return check;
}

void	finish_fd(t_shell *shell, t_cmd *cmd, int p[2], int std[2])
{
	if(shell && cmd->next && p[READ] != -1)
		dup2(p[READ], STDIN_FILENO);
	else
	{
		dup2(std[READ], STDIN_FILENO);
		dup2(std[WRITE], STDOUT_FILENO);
	}
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
			//ft_putendl_fd(path, 1);
			if (stat(path, &stbuf) == -1){
				//ft_putendl_fd(strerror(errno), STDERR_FILENO);
				continue;
			}
			if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
				continue;
			//fprintf(shell->debug_file, "*** %s ***\n", dp->d_name);
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

char **get_env(t_env *env)
{
	int len = 0;
	t_env *cur = env;
	while(cur)
	{
		len++;
		cur = cur->next;
	}
	len++;
	char **tab = (char**)malloc(sizeof(char*)*len);
	cur = env;
	int i = 0;
	while(cur)
	{
		tab[i] = ft_specialjoin(cur->key, cur->value, '=');
		//ft_putendl_fd(tab[i], 1);
		i++;
		cur = cur->next;
	}
	tab[i] = NULL;
	return tab;
}

void	execute_non_builtin(t_shell *shell, t_cmd *cmd)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		char **envp = get_env(shell->envs);
		fprintf(shell->debug_file, "executable: %s\n",cmd->executable);
		int x = execve(cmd->executable, cmd->args, envp);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(x);
	}
	else if (pid > 0)
	{
		int status;

		status = 2;
		fprintf(shell->debug_file, "parent process here\n");
		if(cmd->next)
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
			prepare_fd(cmd, p, std);
			if ((index = get_real_cmd(shell, cmd)) != -1)
				execute_builtin(shell, cmd, index);
			else
			{
				execute_non_builtin(shell, cmd);
			}
			fprintf(shell->debug_file, "command: %s\n", cmd->executable);
			finish_fd(shell, cmd, p, std);
			cmd = cmd->next;
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


