#include "../headers/minishell.h"

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

char *get_file_name(char *str, int save, int *index, int count)
{
	save = *index;
	*index += count;
	char *tmp;
	while (str[*index] == ' ')
		(*index)++;
	while (str[*index] != '\0' && str[*index] != '>' && str[*index] != '<' && str[*index] != ' ')
		(*index)++;
	tmp = ft_substr(str, save + count, *index);
	char *tmp1 = ft_substr(str, *index, ft_strlen(str));
	str[save - 1] = '\0';
	char *tmp2 = str;
	str = ft_strjoin(tmp2, tmp1);
	free(tmp1);
	free(tmp2);
	*index = save - 1;
	return (tmp);
}

void add_file_to_list(t_cmd *cmd, t_files *file)
{
	t_files *current;

	current = cmd->files;
	if (current == NULL)
		cmd->files = file;
	else
	{
		while (current->next)
			current = current->next;
		current->next = file;
	}
}

void ft_find_file(char *str, t_cmd *cmd)
{
	int i = 0;
	int save;
	t_files *file;

	file = (t_files *)malloc(sizeof(t_files));
	file->next = NULL;
	while (str[i])
	{
		file->type = '0';
		if (str[i] == '>' && str[i + 1] == '>')
		{
			file->type = '>';
			file->name = get_file_name(str, save, &i, 2);
		}
		else if (str[i] == '>')
		{
			file->type = 'a';
			file->name = get_file_name(str, save, &i, 1);
		}
		else if (str[i] == '<')
		{
			file->type = '<';
			file->name = get_file_name(str, save, &i, 1);
		}
		if (file->type != '0')
		{
			add_file_to_list(cmd, file);
			file = (t_files *)malloc(sizeof(t_files));
		}
		i++;
	}
}

void add_new_cmd(t_getl *getl, int i)
{
	t_cmd *cmd;
	getl->sp_p = ft_split(getl->sp_c[i], '|');
	int index = -1;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->next = NULL;
	while (getl->sp_p[++index])
	{
		// printf("**%s**\n", getl->sp_p[index]);
		ft_find_file(getl->sp_p[index], cmd);
		getl->sp_s = ft_split(getl->sp_p[index], ' ');
		int j = -1;
		while (getl->sp_s[++j])
		{
			printf("++%s++\n", getl->sp_s[j]);
			//if ()
		}
		write(1, "\n", 1);
		ft_free(getl->sp_s);
	}
	ft_free(getl->sp_p);
}

void get_command(t_getl *getl)
{
	int i;

	i = -1;
	getl->sp_c = ft_split(getl->line, ';');
	while (getl->sp_c[++i])
	{
		// printf("--|%s|--\n", getl->sp_c[i]);
		add_new_cmd(getl, i);
	}
	ft_free(getl->sp_c);
}
