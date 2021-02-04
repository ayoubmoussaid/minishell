
#include "../headers/minishell.h"

int		parse_files(t_cmd *cmd)
{
	t_files *iterator;

	cmd->fdr = -2;
	cmd->fdw = -2;
	iterator = cmd->files;
	int no_error = 1;
	while(iterator && no_error)
	{
		if (iterator->type == 'a' || iterator->type == '>')
		{
			if(cmd->fdw != -2)
				close(cmd->fdw);
			if((cmd->fdw = open(iterator->name, O_WRONLY | O_CREAT | (iterator->type == '>' ? O_TRUNC : O_APPEND), 0644)) < 0)
				no_error = 0;
		}
		else
		{
			if(cmd->fdr != -2)
				close(cmd->fdr);
			if((cmd->fdr = open(iterator->name, O_RDONLY)) < 0)
				no_error = 0;
		}
		iterator = iterator->next;
	}
	if(!no_error){
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	dup_close(int fd1, int fd2)
{
	ft_putstr_fd("fd1: ", 2);
	ft_putnbr_fd(fd1, 2);
	ft_putstr_fd("\n", 2);
	if (dup2(fd1, fd2) == -1)
		perror("Dup1");
	close(fd1);
	//g_fd_table[g_fd_index++] = fd1;
}

int		prepare_fd(t_cmd *cmd, int *p, int *std)
{
	int check = parse_files(cmd);
	if(cmd->next && pipe(p) == 0)
	{
		//printf("p[0] == %d p[1] == %d\n", p[0], p[1]);
		dup_close(p[WRITE], STDOUT_FILENO);
	}
	if(cmd->next == NULL)
	{
		dup_close(std[STDOUT_FILENO], STDOUT_FILENO);
	}
	if(cmd->files && cmd->fdw > 0)
		dup_close(cmd->fdw, STDOUT_FILENO);
	if(cmd->files && cmd->fdr > 0)
		dup_close(cmd->fdr, STDIN_FILENO);
	return check;
}

void	finish_fd(t_cmd *cmd, int *p, int *std)
{
	if(cmd->next)
		dup_close(p[READ], STDIN_FILENO);
	else
	{
		dup_close(std[STDIN_FILENO], STDIN_FILENO);
		//dup_close(std[STDOUT_FILENO], STDOUT_FILENO);
	}
}
