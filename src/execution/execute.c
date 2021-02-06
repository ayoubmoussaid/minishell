
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
	tab[1] = ft_strdup("wassup");
	tab[2] = ft_strdup("bro");
	tab[3] = NULL;
	cmd = create_one(tab[0], tab, NULL);
	char **tab1 = (char**)malloc(sizeof(char*)*3);
	tab1[0] = ft_strdup("echo");
	tab1[1] = NULL;
	tab1[2] = NULL;
	cmd->next = create_one(tab1[0], tab1, get_one_file("bro2", '>'));
	char **tab2 = (char**)malloc(sizeof(char*)*4);
	tab2[0] = ft_strdup("echo");
	tab2[1] = ft_strdup("hello");
	tab2[2] = NULL;
	tab2[3] = NULL;
	cmd->next->next = create_one(tab2[0], tab2, NULL);

	return (cmd);
}
//--------------------------------------------------------------------------

int	execute_builtin(t_cmd *cmd, int index)
{
	static int (*builtin_functions[7])(t_cmd *cmd) = {ft_echo, ft_pwd, ft_cd, ft_env, ft_export, ft_unset, ft_exit};
	return (builtin_functions[index](cmd));
}

void	execute_command(t_cmd *cmd, int index)
{
	if((g_pid = fork()) == 0)
	{
		if(index >= 0)
			exit(execute_builtin(cmd, index));
		else
			exit(execve(cmd->executable, cmd->args, get_env(g_shell->envs)));	
	}
	else if(g_pid > 0)
		cmd->pid = g_pid;
	if(g_pid < 0)
		error_handle(E_STANDARD, 1, NULL);
}

void	execute()
{
	t_cmd		*cmd;
	int			*p;
	int			*std;
	int			index;
	
	p = (int*)malloc(sizeof(int) * 2);
	std = (int*)malloc(sizeof(int) * 2);
	cmd = g_shell->cmd;
	std[STDIN_FILENO] = dup(STDIN_FILENO);
	std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while(cmd)
	{
		if(!prepare_fd(cmd, p, std))
		{
			cmd = cmd->next;
			continue ;
		}
		if((index = get_real_cmd(cmd)) != -2)
			execute_command(cmd, index);
		else
			error_handle(E_CNF, errno, cmd->c);
		finish_fd(cmd, p, std);
		cmd = cmd->next;
	}
	waitpid(g_pid, &(g_shell->exit_status), 0);
	cmd = g_shell->cmd;
	while (cmd->next)
	{
		kill(cmd->pid, SIGPIPE);
		cmd = cmd->next;
	}
	free(p);
	free(std);
}

void	do_the_work(char **env)
{
	g_shell = (t_shell*)malloc(sizeof(t_shell));
	g_shell->envs = NULL;
	g_shell->cmd = create_fake_cmd();
	g_shell->debug_file = fopen("debug.txt", "w");
	my_env(env);
}

