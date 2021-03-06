/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:22:52 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 17:24:25 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		check_for_slash(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i] != '\0')
		if (str[i] == '/')
			return (1);
	return (0);
}

int		check_builtins(char *str)
{
	int	i;

	i = -1;
	while (g_builtins[++i])
		if (ft_strcmp(g_builtins[i], str) == 0)
			return (i);
	return (-1);
}

char	*parse_path(char *all_paths, char *name)
{
	char		**path;
	int			index;
	char		*full_path;
	struct stat	buf;

	index = 0;
	path = ft_split(all_paths, ':');
	while (path[index])
	{
		if (path[index][ft_strlen(path[index])] == '/')
			path[index][ft_strlen(path[index])] = 0;
		full_path = ft_strjoin(path[index], name);
		if (stat(full_path, &buf) == 0 && !S_ISDIR(buf.st_mode))
		{
			ft_free(path);
			return (full_path);
		}
		free(full_path);
		index++;
	}
	ft_free(path);
	return (NULL);
}

void	get_path(t_cmd *cmd)
{
	char	*path;
	char	*name;

	name = ft_strjoin("/", cmd->c);
	path = get_env_var("PATH");
	cmd->executable = parse_path(path, name);
	free(name);
	free(path);
}

int		get_real_cmd(t_cmd *cmd, int *index)
{
	struct stat	buf;

	if ((*index = check_builtins(cmd->c)) != -1 || check_for_slash(cmd->c))
		cmd->executable = ft_strdup(cmd->c);
	else
		get_path(cmd);
	if (*index == -1 && cmd->executable == NULL)
		return (error_handle(E_CNF, 127, cmd->c));
	else if (*index == -1 && stat(cmd->executable, &buf) != 0)
		return (error_handle(E_WPATH, 127, cmd->executable));
	else if (*index == -1 && S_ISDIR(buf.st_mode))
		return (error_handle(E_ISDIR, 126, cmd->executable));
	return (0);
}
