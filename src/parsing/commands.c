#include "../headers/minishell.h"

void ft_print_files_list(t_cmd *cmd)
{
	t_files *current = cmd->files;
	write(1, "\nstar files list\n\n\n", 18);
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
	printf("*********************startlist cmd*********************\n");
	t_cmd *current;

	current = cmd;
	while (current)
	{
		ft_print_tab(current->args);
		printf("myyyyyyy c %s\n", current->c);
		ft_print_files_list(current);
		current = current->next;
	}
	printf("*********************end list cmd*********************\n");
}

void ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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
	char *tmp1 = ft_substr(*str, *index, ft_strlen(*str));
	(*str)[save] = '\0';
	char *tmp2 = *str;
	*str = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
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
	free(file);
	// printf("+++++%s\n", *str);
}

void add_cmd_to_list(t_cmd *cmd)
{
	t_cmd *current;

	cmd->next = NULL;
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

void ft_to_pos(char **s)
{
	int i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] < 0)
			(*s)[i] = -(*s)[i];
		i++;
	}
	if(ft_strcmp(*s, "\"\"") == 0 || ft_strcmp(*s, "\'\'") == 0)
	{
		free(*s);
		*s = ft_strdup("");
	}
}

void ft_fix_neg_cmd(t_cmd *cmd)
{
	t_files *file;
	int i;

	i = -1;
	file = cmd->files;
	while (file)
	{
		ft_to_pos(&(file->name));
		file = file->next;
	}
	while (cmd->args[++i])
		ft_to_pos(&(cmd->args[i]));
}

void fill_cmd(t_getl *g_getl, int i)
{
	t_cmd *cmd;
	int index;

	index = -1;
	g_getl->sp_p = ft_split(g_getl->sp_c[i], '|');
	while (g_getl->sp_p[++index])
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmd->files = NULL;
		cmd->next = NULL;
		ft_find_file(&g_getl->sp_p[index], cmd);
		cmd->args = ft_split(g_getl->sp_p[index], ' '); //TODO check the split here
		ft_fix_neg_cmd(cmd);
		cmd->c = cmd->args[0];
		add_cmd_to_list(cmd);
	}
	ft_free(g_getl->sp_p);
}

void ft_clear_files_list(t_cmd *cmd)
{
	t_files *current = cmd->files;
	t_files *next = NULL;

	while (current)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = NULL;
		current = next;
	}
	cmd->files = NULL;
}

void ft_clear_cmd_list()
{
	t_cmd *current;
	t_cmd *next;

	current = g_shell->cmd;
	next = NULL;
	while (current)
	{
		next = current->next;
		free(current->executable);
		ft_clear_files_list(current);
		ft_free(current->args);
		current->args = NULL;
		current->executable = NULL;
		free(current);
		current = next;
	}
	//g_shell->cmd = NULL;
}

void get_command(t_getl *g_getl)
{
	int i;

	i = -1;
	g_getl->sp_c = ft_split(g_getl->line, ';');
	while (g_getl->sp_c[++i])
	{
		g_shell->cmd = NULL;
		flip_line(&(g_getl->sp_c[i]));
		fill_cmd(g_getl, i);
		execute();
		ft_clear_cmd_list();
		g_pid = 0;
	}
	ft_free(g_getl->sp_c);
}
