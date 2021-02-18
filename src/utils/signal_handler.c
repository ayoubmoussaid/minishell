#include "../headers/minishell.h"

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
