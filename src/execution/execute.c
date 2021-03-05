
#include "../headers/minishell.h"

int execute_builtin(t_cmd *cmd, int index)
{
	static int (*builtin_functions[7])(t_cmd * cmd) = {ft_echo, ft_pwd, ft_cd, ft_env, ft_export, ft_unset, ft_exit};
	return (builtin_functions[index](cmd));
}

void execute_command(t_cmd *cmd, int index, int *p)
{
	if (index >= 0 && g_simple_cmd)
		g_shell->exit_status = execute_builtin(cmd, index);
	if (!(index >= 0 && g_simple_cmd) && (g_pid = fork()) == 0)
	{
		if(!g_simple_cmd)
			close(p[READ]);
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


static	void	set_return()
{
	int			ret;
	int			data;

	ret = 0;
	data = 0;
	while (ret != -1)
	{
		//write(2, "hi\n", 3);
		ret = wait(&data);
		if (ret == g_pid && WIFEXITED(data))
			g_shell->exit_status = WEXITSTATUS(data);
		else if (ret == g_pid && WIFSIGNALED(data))
		{
			g_shell->exit_status = 128 + WTERMSIG(data);
			WTERMSIG(data) == SIGQUIT ? write(1, "Quit\n", 5) : 1;
		}
	}
	g_pid = 0;
}

void execute()
{
	t_cmd *cmd;
	int *p;
	int *std;
	int index;
	int to_break;

	to_break = 1;
	p = (int *)malloc(sizeof(int) * 2);
	std = (int *)malloc(sizeof(int) * 2);
	cmd = g_shell->cmd;
	std[STDIN_FILENO] = dup(STDIN_FILENO);
	std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	g_simple_cmd = cmd->next == NULL ? 1 : 0;
	while (cmd && to_break)
	{
		if (prepare_fd(cmd, p, std) && cmd->c)
		{
			if (get_real_cmd(cmd, &index) == 0 && cmd->executable)
				execute_command(cmd, index, p);
		}
		finish_fd(cmd, p, std);
		cmd = cmd->next;
	}
	set_return();
	close(std[0]);
	close(std[1]);
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
