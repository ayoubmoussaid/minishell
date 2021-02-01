/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/01 11:19:17 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

char	*g_builtins[] = {"echo", "pwd", "cd", "env", "export", "unset", "exit", (void*)0};


void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("\n", STDOUT_FILENO);
		g_shell->exit_status = 128 + sig;
	}
	if (sig == SIGQUIT)
	{
		//if (getpid() == 0)
		write(1, "\b \b\b \b", 6);
	}
}

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

t_files *get_one_file(char *name, char type){
	t_files *file = (t_files*)malloc(sizeof(t_files));
	file->name = ft_strdup(name);
	file->type = type;
	file->next = NULL;
	// file->next =(t_files*)malloc(sizeof(t_files));
	// file->next->name = ft_strdup("testing1");
	// file->next->type = '<';
	// file->next->next =(t_files*)malloc(sizeof(t_files)); 
	// file->next->next->name = ft_strdup("testing2");
	// file->next->next->type = '<';
	// file->next->next->next = NULL;
	return file;
}

t_pipeline	*create_fake_cmd()
{
	t_pipeline *pipeline;
	pipeline = (t_pipeline*)malloc((sizeof(t_pipeline)));
	char **tab = (char**)malloc(sizeof(char*)*5);
	tab[0] = ft_strdup("echo");
	tab[1] = ft_strdup("-n");
	tab[2] = ft_strdup("-n");
	tab[3] = ft_strdup("what");
	tab[4] = NULL;
	pipeline->pipe = create_one(tab[0], tab, NULL);
	// char **tab1 = (char**)malloc(sizeof(char*)*3);
	// tab1[0] = ft_strdup("cat");
	// tab1[1] = ft_strdup("-e");
	// tab1[2] = NULL;
	// pipeline->pipe->next = create_one(tab1[0], tab1, NULL);
	// char **tab2 = (char**)malloc(sizeof(char*)*3);
	// tab2[0] = ft_strdup("grep");
	// tab2[1] = ft_strdup("l");
	// tab2[2] = NULL;
	// pipeline->pipe->next->next = create_one(tab2[0], tab2, NULL);

	// char **tab3 = (char**)malloc(sizeof(char*)*2);
	// tab3[0] = ft_strdup("pwd");
	// tab3[1] = NULL;
	// pipeline->next = (t_pipeline*)malloc(sizeof(t_pipeline));
	// pipeline->next->pipe = create_one(tab3[0], tab3, NULL);
	// char **tab2 = (char**)malloc(sizeof(char*)*3);
	// tab2[0] = ft_strdup("grep");
	// tab2[1] = ft_strdup("l");
	// tab2[2] = NULL;
	// pipeline->next->pipe->next = create_one(tab2[0], tab2, NULL);
	// pipeline->next->next = NULL;

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

void dup_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

int	prepare_fd(t_cmd *cmd, int p[2], int std[2])
{
	int check = parse_files(cmd);
	if(cmd->next && pipe(p) == 0)
		dup_close(p[WRITE], STDOUT_FILENO);
	if(cmd->next == NULL)
		dup2(std[WRITE], STDOUT_FILENO);
	if(cmd->files && cmd->fdw > 0)
		dup_close(cmd->fdw, STDOUT_FILENO);
	if(cmd->files && cmd->fdr > 0)
		dup_close(cmd->fdr, STDIN_FILENO);
	return check;
}

void	finish_fd(t_cmd *cmd, int p[2], int std[2])
{
	if(g_shell && cmd->next && p[READ] != -1)
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

char	*get_path( t_cmd	*cmd)
{
	char			*path;
	char			**all_paths;
	int				i;
	DIR				*dfd;
	struct dirent	*dp;
	struct stat		stbuf;

	i = -1;
	path = get_env_var("PATH");
	all_paths = ft_split(path, ':');
	while (all_paths[++i] != 0)
	{
		//fprintf(g_shell->debug_file, "************ %s ************\n", all_paths[i]);
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
			//fprintf(g_shell->debug_file, "*** %s ***\n", dp->d_name);
			if(ft_strcmp(dp->d_name, cmd->c) == 0)
				return (path);
		}
		closedir(dfd);
	}
	return "hi";
}

int 	get_real_cmd( t_cmd *cmd)
{
	int		index;

	index = -1;
	
	if(check_for_slash(cmd->c) || (index = check_builtins(cmd->c)) != -1)
		cmd->executable = cmd->c;
	else
		cmd->executable = get_path(cmd);
	return (index);
}

void	execute_builtin( t_cmd *cmd, int index)
{
	static void (*builtin_functions[7])( t_cmd *cmd) = {ft_echo, ft_pwd, ft_cd, ft_env, ft_export, ft_unset, ft_exit};
	builtin_functions[index](cmd);
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

void	execute_non_builtin( t_cmd *cmd)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		char **envp = get_env(g_shell->envs);
		fprintf(g_shell->debug_file, "executable: %s\n",cmd->executable);
		int x = execve(cmd->executable, cmd->args, envp);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(x);
	}
	else if (pid > 0)
	{
		int status;

		status = 2;
		fprintf(g_shell->debug_file, "parent process here\n");
		if(!cmd->next){
			waitpid(pid, &status, 0);
			g_shell->exit_status = status;
		}
		fprintf(g_shell->debug_file, "child process exited %d | %d --- status:%d\n", pid, getpid(), status);
	}
}

void	execute()
{
	t_pipeline	*pipeline;
	t_cmd		*cmd;
	int p[2];
	int std[2];
	int index;

	pipeline = g_shell->pipeline;
	std[STDIN_FILENO] = dup(STDIN_FILENO);
	std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while(pipeline)
	{
		cmd = pipeline->pipe;
		fprintf(g_shell->debug_file, "------------------------------\n");
		while(cmd)
		{
			fprintf(g_shell->debug_file, "-- %s --\n", cmd->c);
			prepare_fd(cmd, p, std);
			if ((index = get_real_cmd(cmd)) != -1)
				execute_builtin(cmd, index);
			else
			{
				execute_non_builtin(cmd);
			}
			fprintf(g_shell->debug_file, "command: %s\n", cmd->executable);
			finish_fd(cmd, p, std);
			cmd = cmd->next;
		}

		pipeline = pipeline->next;
	}
}


void	do_the_work(char **env)
{
	g_shell = (t_shell*)malloc(sizeof(t_shell));
	g_shell->envs = NULL;
	g_shell->pipeline = create_fake_cmd();
	//write(1, "\n=============================\n", 31);
	g_shell->debug_file = fopen("debug.txt", "w");
	my_env(env);
	//execute();
}


int get_index_of_separator(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		if(!ft_isalnum(str[i]))
			break ;
		i++;
	}
	return (i);
}

void override_str(char *str, int index)
{
	while(str[index] != '\0')
	{
		str[index] = str[index + 1];
		index++;
	}
}

int check_for_simple_double(int *i, int *s, int *d)
{
	int x = 0;

	if(g_shell->line[*i] == '\"' && *s == 0)
	{
		override_str(g_shell->line, *i);
		*d = !(*d);
		x = 1;
	}
	if(g_shell->line[*i] == '\'' && *d == 0)
	{
		override_str(g_shell->line, *i);
		(*s) = !(*s);
		if(*s == 0)
			(*i)--;
		x = 1;
	}
	return (x);
}

int check_for_after_backslash(char c)
{
	return (c == '$' || c == '\"' || c == '\\');
}

void flip_line()
{
	int i = -1;
	int d = 0;
	int s = 0;
	//TODO variable expansion and backslash handle in double quotes
	while(g_shell->line[++i] != '\0')
	{
		while(check_for_simple_double(&i, &s, &d));
		if(g_shell->line[i] == '$' && s == 0)
		{
			char *tmp1;
			char *tmp2;
			int index = 1;
			if(g_shell->line[i + 1] == '?')
				tmp2  = ft_itoa(g_shell->exit_status);
			else
			{
				index = get_index_of_separator(g_shell->line + i + 1);
				tmp1 = ft_substr(g_shell->line + i + 1, 0, index);
				tmp2 = get_env_var(tmp1);
				tmp2 = tmp2 ? tmp2 : ft_strdup("");
				free(tmp1);
			}
			if(index != 0)
			{
				tmp1 = ft_strjoin(tmp2, g_shell->line + i + index + 1);
				free(tmp2);
				g_shell->line[i] = '\0';
				tmp2 = ft_strjoin(g_shell->line, tmp1);
				free(g_shell->line);
				g_shell->line = tmp2;
			}
		}
		if(d == 1 && g_shell->line[i] == '\\' && check_for_after_backslash(g_shell->line[i + 1]))
			override_str(g_shell->line, i);
		if(d || s)
			g_shell->line[i] = -g_shell->line[i];
	}
	if(d || s)
		ft_putendl_fd("Syntax error", STDERR_FILENO);
}


// void check_line()
// {
// 	int i = 0;

// 	while(g_shell->line[++i] != '\0')
// 	{
// 		if(g_shell->line[i] == '>' || g_shell->line[i] == '<')
// 		{
// 			//get file
// 		}
// 		else if(g_shell->line[i] == '|')
// 		{
// 			//new var ... jump to next of course
// 		}
// 		else
// 		{
// 			//add variable to command
// 		}
// 	}
// }

char  *reflip(char *str)
{
	int i = -1;

	while(str[++i] != '\0')
		if(str[i] < 0)
			str[i] = -str[i];
	return str;
}
int     main(int argc, char **argv, char **env)
{
	
	//signal(SIGINT, signal_handler);
	//signal(SIGQUIT, signal_handler);
	if (argc > 1)
		argv = NULL;
	do_the_work(env);
	g_shell->exit_status = 0;
	while(1)
	{
		ft_putstr_fd("minishell $> ", STDOUT_FILENO);
		get_next_line(STDIN_FILENO, &(g_shell->line));
		//g_shell->line = ft_strdup("hello \"$\"PWD");
		ft_putendl_fd(g_shell->line, STDOUT_FILENO);
		flip_line();
		//check_line();
		ft_putendl_fd(reflip(g_shell->line), STDOUT_FILENO);
		free(g_shell->line);
	}
	fclose(g_shell->debug_file);
	return (0);
}


