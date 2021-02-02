
#include "../headers/minishell.h"




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

t_cmd	*create_fake_cmd()
{
	t_cmd *cmd;
	cmd = (t_cmd*)malloc((sizeof(t_cmd)));
	char **tab = (char**)malloc(sizeof(char*)*5);
	tab[0] = ft_strdup("echo");
	tab[1] = ft_strdup("what");
	tab[2] = NULL;
	cmd = create_one(tab[0], tab, NULL);
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
	return (cmd);
}
//--------------------------------------------------------------------------

void	execute_builtin( t_cmd *cmd, int index)
{
	static int (*builtin_functions[7])(t_cmd *cmd) = {ft_echo, ft_pwd, ft_cd, ft_env, ft_export, ft_unset, ft_exit};
	builtin_functions[index](cmd);
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
	t_cmd		*cmd;
	int p[2];
	int std[2];
	int index;

	cmd = g_shell->cmd;
	std[STDIN_FILENO] = dup(STDIN_FILENO);
	std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	fprintf(g_shell->debug_file, "------------------------------\n");
	while(cmd)
	{
		fprintf(g_shell->debug_file, "-- %s --\n", cmd->c);
		prepare_fd(cmd, p, std);
		if ((index = get_real_cmd(cmd)) >= 0)
			execute_builtin(cmd, index);
		else if(index == -1)
		{
			execute_non_builtin(cmd);
		}
		else
		{
			char *error = ft_strjoin("minishell: ", cmd->c);
			char *tmp = ft_strjoin(error, ": command not found");
			ft_putendl_fd(tmp, STDERR_FILENO);
			free(error);
			free(tmp);
		}
		fprintf(g_shell->debug_file, "command: %s\n", cmd->executable);
		finish_fd(cmd, p, std);
		cmd = cmd->next;
	}

}

void	do_the_work(char **env)
{
	g_shell = (t_shell*)malloc(sizeof(t_shell));
	g_shell->envs = NULL;
	g_shell->cmd = create_fake_cmd();
	//write(1, "\n=============================\n", 31);
	g_shell->debug_file = fopen("debug.txt", "w");
	my_env(env);
}


// char  *reflip(char *str)
// {
// 	int i = -1;

// 	while(str[++i] != '\0')
// 		if(str[i] < 0)
// 			str[i] = -str[i];
// 	return str;
// }
