/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:28:41 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/03/06 18:01:26 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_files	*create_file(void)
{
	t_files	*file;

	file = (t_files*)malloc(sizeof(t_files));
	file->next = NULL;
	return (file);
}

void	ft_find_file(char **str, t_cmd *cmd)
{
	int		i;
	t_files	*file;

	i = -1;
	file = create_file();
	while ((*str)[++i])
	{
		file->type = '0';
		if ((*str)[i] == '>' && (*str)[i + 1] == '>')
		{
			file->type = 'a';
			file->name = get_file_name(str, &i, 2);
		}
		else if ((*str)[i] == '>' || (*str)[i] == '<')
		{
			file->type = ((*str)[i] == '>') ? '>' : '<';
			file->name = get_file_name(str, &i, 1);
		}
		if (file->type != '0')
		{
			add_file_to_list(cmd, file);
			file = create_file();
		}
	}
	free(file);
}

void	add_file_to_list(t_cmd *cmd, t_files *file)
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

void	init_s_get_file(t_get_file *f, int *index, int count)
{
	f->save = *index;
	*index += count;
	f->index_s = 0;
	f->index_e = 0;
}

char	*get_file_name(char **str, int *index, int count)
{
	t_get_file f;

	init_s_get_file(&f, index, count);
	while ((*str)[*index] == ' ')
	{
		(*index)++;
		f.index_s++;
	}
	while ((*str)[*index] != '\0' && (*str)[*index] != '>'
			&& (*str)[*index] != '<' && (*str)[*index] != ' ')
	{
		(*index)++;
		f.index_e++;
	}
	f.tmp = ft_substr(*str, f.save + count + f.index_s, f.index_e);
	f.tmp1 = ft_substr(*str, *index, ft_strlen(*str));
	(*str)[f.save] = '\0';
	f.tmp2 = *str;
	*str = ft_strjoin(f.tmp2, f.tmp1);
	free(f.tmp1);
	free(f.tmp2);
	*index = f.save - 1;
	return (f.tmp);
}
