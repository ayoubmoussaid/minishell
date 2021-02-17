#include "../headers/minishell.h"

void ft_print_files_list(t_cmd *cmd)
{
	t_files *current = cmd->files->next;
	write(1, "\nstar tfiles list\n\n\n", 15);
	while (current)
	{
		printf("----|%s|%c|\n\n", current->name, current->type);
		current = current->next;
	}
	write(1, "end files list\n\n\n", 15);
}

void ft_print_tab(char **args)
{
	int i = 0;
	while (args[i])
	{
		printf("---args[%d] = %s\n", i, args[i]);
		i++;
	}
}

void ft_print_cmd_list(t_cmd *cmd)
{
	t_cmd *current;

	current = cmd;
	while (current)
	{
		printf("startlist cmd*********************\n");
		ft_print_tab(current->args);
		printf("myyyyyyy c %s\n", current->c);
		ft_print_files_list(current);
		current = current->next;
	}
	write(1, "*******************end list cmd\n\n", 13);
}

void ft_free(char **s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
	s = NULL;
}

int sp_len(char **str)
{
	int i;

	i = 0;
	while (*str)
		i++;
	return (i);
}

char *get_file_name(char **str, int *index, int count)
{
	int save = *index;
	int index_s = 0;
	int index_e = 0;

	*index += count;
	char *tmp;
	while ((*str)[*index] == ' ')
	{
		(*index)++;
		index_s++;
	}
	while ((*str)[*index] != '\0' && (*str)[*index] != '>' && (*str)[*index] != '<' && (*str)[*index] != ' ')
	{
		(*index)++;
		index_e++;
	}
	tmp = ft_substr(*str, save + count + index_s, index_e);
	// printf("file name:|%s|\n", tmp);
	char *tmp1 = ft_substr(*str, *index, ft_strlen(*str));
	(*str)[save] = '\0';
	char *tmp2 = *str;
	*str = ft_strjoin(tmp2, tmp1);

	// printf("new str:|%s|\n", *str);
	// free(tmp1); ///////// showen err break Point: freed was not allocated
	// free(tmp2);
	// tmp1 = tmp2 = NULL;
	*index = save - 1;
	return (tmp);
}

void add_file_to_list(t_cmd *cmd, t_files *file)
{
	// printf("---------------%s|%p|%p\n", file->name, file, cmd);
	t_files *current = cmd->files;
	if (current == NULL)
		cmd->files = file;
	else
	{
		while (current->next)
			current = current->next;
		current->next = file;
	}
}

void ft_find_file(char **str, t_cmd *cmd)
{
	int i = 0;
	t_files *file;

	file = (t_files *)malloc(sizeof(t_files));
	file->next = NULL;
	while ((*str)[i])
	{
		file->type = '0';
		if ((*str)[i] == '>' && (*str)[i + 1] == '>')
		{
			file->type = 'a';
			file->name = get_file_name(str, &i, 2);
		}
		else if ((*str)[i] == '>')
		{
			file->type = '>';
			file->name = get_file_name(str, &i, 1);
		}
		else if ((*str)[i] == '<')
		{
			file->type = '<';
			file->name = get_file_name(str, &i, 1);
		}
		if (file->type != '0')
		{
			add_file_to_list(cmd, file);
			file = (t_files *)malloc(sizeof(t_files));
			file->next = NULL;
		}
		i++;
	}
	// printf("+++++%s\n", *str);
}

void add_cmd_to_list(t_cmd *cmd)
{
	t_cmd *current;

	current = g_shell->cmd;
	if (current == NULL)
	{
		g_shell->cmd = cmd;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = cmd;
	}
}

void fill_cmd(t_getl *getl, int i)
{
	t_cmd *cmd;
	int index;

	index = -1;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->files = (t_files *)malloc(sizeof(t_files));
	cmd->next = NULL;
	cmd->files->next = NULL;
	getl->sp_p = ft_split(getl->sp_c[i], '|');
	while (getl->sp_p[++index])
	{
		ft_find_file(&getl->sp_p[index], cmd);
		cmd->args = ft_split(getl->sp_p[index], ' ');
		cmd->c = cmd->args[0];
		// ft_print_list(cmd);
		// ft_print_tab(cmd->args);
		add_cmd_to_list(cmd);
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmd->files = (t_files *)malloc(sizeof(t_files));
	}
}

void ft_clear_files_list(t_cmd *cmd)
{
	t_files *current = cmd->files->next;
	t_files *next = NULL;

	ft_print_files_list(cmd);
	while (current)
	{
		next = current->next;
		free(current);
		current = NULL;
		current = next;
	}
	cmd->files->next = NULL;
	ft_print_files_list(cmd);
	printf("\n\n\n\n\n\n\n\n");
}

void ft_clear_cmd_list(t_cmd *cmd)
{
	// ft_print_cmd_list(cmd);
	t_cmd *current;
	t_cmd *next;

	current = cmd;
	next = NULL;
	while (current)
	{

		next = current->next;
		ft_clear_files_list(current);
		// ft_free(current->args);
		free(current->c);
		// free(current);
		current = next;
	}
	g_shell->cmd = NULL;
	// ft_print_cmd_list(cmd);
}

void get_command(t_getl *getl)
{
	int i;

	i = -1;
	getl->sp_c = ft_split(getl->line, ';');
	while (getl->sp_c[++i])
	{
		//clear linked list of cmd->cmd->cmd->cmd(cmd1); and move to cmd2 (cmd1;cmd2;)
		//cear g_shell->cmd for the second command to be filled

		ft_clear_cmd_list(g_shell->cmd);
		fill_cmd(getl, i);
		// ft_print_cmd_list(g_shell->cmd);
	}

	// ft_clear_cmd_list(g_shell->cmd);
	ft_free(getl->sp_c);
}
