/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:30:33 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 18:09:29 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_updatepwd(const char *prop, char *value)
{
	t_env	*current;

	current = g_shell->envs;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, prop) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
		}
		current = current->next;
	}
}

void	norm_free(char **str1, char **str2, char **str3)
{
	free(*str1);
	free(*str2);
	free(*str3);
}

int		norm_reduce(char **dir, char **args)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = get_env_var("HOME");
	tmp2 = args[1] ? args[1] + 1 : "";
	*dir = ft_strjoin(tmp1, tmp2);
	if (ft_strlen(tmp1) == 0)
	{
		error_handle(E_CD_HOME, 1, *dir);
		free(tmp1);
		free(*dir);
		return (1);
	}
	free(tmp1);
	return (0);
}

int		norm_dir(char **dir)
{
	char	*olddir;
	char	*newdir;
	int		ret;

	olddir = getcwd(NULL, 0);
	ret = chdir(*dir);
	newdir = getcwd(NULL, 0);
	if (ret == 0 && olddir && newdir)
	{
		ft_updatepwd("OLDPWD", olddir);
		ft_updatepwd("PWD", newdir);
	}
	else
	{
		error_handle(E_CD_NOFOD, 1, *dir);
		norm_free(&olddir, dir, &newdir);
		return (1);
	}
	norm_free(&olddir, dir, &newdir);
	return (0);
}

int		ft_cd(t_cmd *cmd)
{
	int		len;
	char	*dir;

	len = ft_len(cmd->args);
	if (len == 1 || (len == 2 && cmd->args[1][0] == '~'))
	{
		if (norm_reduce(&dir, cmd->args))
			return (1);
	}
	else
		dir = ft_strlen(cmd->args[1]) == 0 ?
			ft_strdup(".") : ft_strdup(cmd->args[1]);
	return (norm_dir(&dir));
}
