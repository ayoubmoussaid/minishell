
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
			close(cmd->fdw);
			if((cmd->fdw = open(iterator->name, O_WRONLY | O_CREAT | (iterator->type == '>' ? O_TRUNC : O_APPEND), 0644)) < 0)
				no_error = 0;
		}
		else
		{
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
	dup2(fd1, fd2);
	close(fd1);
}

int		prepare_fd(t_cmd *cmd, int p[2], int std[2])
{
	int check = parse_files(cmd);
	if(cmd->next && pipe(p) == 0)
		dup_close(p[WRITE], STDOUT_FILENO);
	if(cmd->next == NULL)
		dup2(std[WRITE], STDOUT_FILENO);
	if(cmd->files && cmd->fdw > 0)
		dup_close(cmd->fdw, STDOUT_FILENO);
	if(cmd->files && cmd->fdr > 0)
		dup_close(cmd->fdr, STDIN_FILENO);
	return check;
}

void	finish_fd(t_cmd *cmd, int p[2], int std[2])
{
	if(cmd->next && p[READ] != -1)
		dup2(p[READ], STDIN_FILENO);
	else
	{
		dup2(std[READ], STDIN_FILENO);
		dup2(std[WRITE], STDOUT_FILENO);
	}
}
