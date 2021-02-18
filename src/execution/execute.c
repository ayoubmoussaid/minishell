
#include "../headers/minishell.h"

int execute_builtin(t_cmd *cmd, int index)
{
	static int (*builtin_functions[7])(t_cmd * cmd) = {ft_echo, ft_pwd, ft_cd, ft_env, ft_export, ft_unset, ft_exit};
	return (builtin_functions[index](cmd));
}

void execute_command(t_cmd *cmd, int index)
{
	if (index >= 0 && cmd->next == NULL)
		execute_builtin(cmd, index);
	if (!(index >= 0 && cmd->next == NULL) && (g_pid = fork()) == 0)
	{
		if (index >= 0)
			exit(execute_builtin(cmd, index));
		else
			exit(execve(cmd->executable, cmd->args, get_env(g_shell->envs)));
	}
	else if (g_pid > 0)
		cmd->pid = g_pid;
	if (g_pid < 0)
		error_handle(E_STANDARD, 1, NULL);
}

void execute()
{
	t_cmd *cmd;
	int *p;
	int *std;
	int index;

	p = (int *)malloc(sizeof(int) * 2);
	std = (int *)malloc(sizeof(int) * 2);
	cmd = g_shell->cmd;
	std[STDIN_FILENO] = dup(STDIN_FILENO);
	std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while (cmd)
	{
		if (!prepare_fd(cmd, p, std))
		{
			cmd = cmd->next;
			continue;
		}
		if ((index = get_real_cmd(cmd)) != -2)
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

void do_the_work(char **env)
{
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	g_shell->envs = NULL;
	g_shell->debug_file = fopen("debug.txt", "w");
	my_env(env);
}
