#include "../headers/minishell.h"

void signal_handler(int sig)
{
	if (sig == SIGINT && g_pid == 0)
	{
		ft_putstr_fd("\033[91m\nminishell$> \033[39m", STDOUT_FILENO);
		g_shell->exit_status = 128 + sig;
		//get_next_line(-5, NULL);
	}
	if (sig == SIGQUIT)
	{
		if (g_pid == 0)
			write(1, "\b \b\b \b", 6);
		else 
			write(1, "Quit\n", 5);
	}
}
