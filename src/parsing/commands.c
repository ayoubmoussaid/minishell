#include "../headers/minishell.h"

void ft_print_list(t_cmd *cmd)
{
	t_files *current = cmd->files;
	while (current)
	{
		printf("|%s|%c|%p|\n\n", current->name, current->type, current->next);
		current = current->next;
	}

	write(1, "endlist\n\n\n", 10);
}

void ft_print_tab(char **args)
{
	int i = 0;
	while (args[i])
	{
		printf("args[%d] = %s\n", i, args[i]);
		i++;
	}
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
	printf("%p|%s|%p\n", cmd->files, file->name, file);
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
	current = (t_cmd *)malloc(sizeof(t_cmd));
	current = g_shell->cmd;

	if (current == NULL)
	{
		current = cmd;
		// printf("%s|%p|\n", cmd->c, cmd->next);
		// ft_print_list(cmd);
	}
	else
	{
		while (current)
			current = current->next;
		current = cmd;
		// printf("%s|%p|\n", cmd->c, cmd->next);
		// ft_print_list(cmd);
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
		//clear ;

		ft_find_file(&getl->sp_p[index], cmd);
		cmd->args = ft_split(getl->sp_p[index], ' ');
		cmd->c = cmd->args[0];
		// ft_print_list(cmd);
		// ft_print_tab(cmd->args);
		// add_cmd_to_list(cmd);
	}
}

void get_command(t_getl *getl)
{
	int i;

	i = -1;
	getl->sp_c = ft_split(getl->line, ';');
	while (getl->sp_c[++i])
	{
		//cear g_shell->cmd for the second command to be filled
		fill_cmd(getl, i);
	}
	ft_free(getl->sp_c);
}
