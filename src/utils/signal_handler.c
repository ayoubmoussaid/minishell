#include "../headers/minishell.h"

void signal_handler(int sig)
{
	if (sig == SIGINT && g_pid == 0)
	{
		ft_putstr_fd("\b\b  \b\b\033[91m\nminishell$> \033[39m", STDOUT_FILENO);
		if(ft_strlen(g_getl->line) == 0)
			g_shell->exit_status = 1;
		else
			g_shell->exit_status = 128 + sig;
	}
	if (sig == SIGQUIT)
	{
		if (g_pid == 0)
			write(1, "\b \b\b \b", 6);
	}
}
