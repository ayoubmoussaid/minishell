#include "minishell.h"


int		count_char(char *str, char c)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			x++;
		i++;
	}
	return x;
}

void	check_redirections(char *str, t_commands *cmd)
{
	//you missed redirections ... to be done tomorrow inshaallah
}


void	check_pipe_existance(char *str, t_commands *cmd)
{
	char **obj;
	int i = 0;

	cmd->pipe = search_char(str, '|');
	obj = ft_split(str, '|');
	while (obj[i] != 0)
	{
		
	}
}

int     check_for_parse_error(char *str)
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
	if (check_for_parse_error(cmd->line))
		return 1;
	cmd->command = ft_split(cmd->line, ';');
	int i = 0;
	while(cmd->command[i] != 0)
		check_pipe_existance(cmd->command[i++], cmd);
	return 0;
}

int     main(int argc, char **argv)
{
	t_commands *cmd;
	cmd = (t_commands*)malloc(sizeof(t_commands));
	cmd->pipe = 0;
	while(1)
		if (read_terminal(cmd))
			break ;

	printf("end");
	return (0);
}