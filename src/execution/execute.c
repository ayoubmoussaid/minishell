/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:17:38 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 16:27:07 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int			execute_builtin(t_cmd *cmd, int index)
{
	static int (*builtin_functions[7])(t_cmd *cmd) = {ft_echo,
		ft_pwd, ft_cd, ft_env, ft_export, ft_unset, ft_exit};

	return (builtin_functions[index](cmd));
}

void		execute_command(t_cmd *cmd, int index, int *p)
{
	if (index >= 0 && g_simple_cmd)
		g_shell->exit_status = execute_builtin(cmd, index);
	if (!(index >= 0 && g_simple_cmd) && (g_pid = fork()) == 0)
	{
		if (!g_simple_cmd)
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

static void	set_return(void)
{
	int			ret;
	int			data;

	ret = 0;
	data = 0;
	while (ret != -1)
	{
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

void		init_execute(int **std, int **p, int *to_break, int check)
{
	*to_break = 1;
	*p = (int *)malloc(sizeof(int) * 2);
	*std = (int *)malloc(sizeof(int) * 2);
	(*std)[STDIN_FILENO] = dup(STDIN_FILENO);
	(*std)[STDOUT_FILENO] = dup(STDOUT_FILENO);
	g_simple_cmd = check ? 1 : 0;
}

void		execute(void)
{
	t_cmd	*cmd;
	int		*p;
	int		*std;
	int		index;
	int		to_break;

	cmd = g_shell->cmd;
	init_execute(&std, &p, &to_break, cmd->next == NULL);
	while (cmd && to_break)
	{
		if (prepare_fd(cmd, p, std) && cmd->c)
		{
			if (get_real_cmd(cmd, &index) == 0 && cmd->executable)
				execute_command(cmd, index, p);
		}
		else
			cmd->executable = ft_strdup("");
		finish_fd(cmd, p, std);
		cmd = cmd->next;
	}
	set_return();
	close(std[0]);
	close(std[1]);
	free(p);
	free(std);
}
