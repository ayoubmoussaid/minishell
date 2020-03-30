#include "minishell.h"


void	check_pipe_existance(char *str, t_commands *cmd)
{
	char **obj;

	obj = ft_split(str, '|');
}

int     check_for_parse(char *str)
{
	int i = 0;
	int size = ft_strlen(str);
	
	while (i < size - 1 && !(str[i] == ';' && str[i + 1] == ';'))
	{
		ft_putchar_fd(str[i],1);
		i++;
	}
	if ( i == size - 1 )
		return (0);
	else
	{
		ft_putendl_fd("minishell: parse error near `;;'", 1);
		return (1);
	}
}

int    read_terminal(t_commands *cmd)
{
	get_next_line(0, &(cmd->line));
	ft_putendl_fd(cmd->line, 1);
	if (check_for_parse(cmd->line))
		return 1;
	cmd->command = ft_split(cmd->line, ';');
	int i = 0;
	while(cmd->command[i] != 0)
		ft_putendl_fd(cmd->command[i++], 1);
	return 0;
}

int     main(int argc, char **argv)
{
	t_commands *cmd;
	cmd = (t_commands*)malloc(sizeof(t_commands));
	while(1)
		if (read_terminal(cmd))
			break ;

	printf("end");
	return (0);
}