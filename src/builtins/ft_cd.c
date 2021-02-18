/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:30:33 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/18 11:57:55 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char *ft_specialjoin(char const *s1, char const *s2, char c)
{
	char *newstr;
	unsigned int i;
	unsigned int n;
	unsigned int m;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen((char *)s1) + 1;
	m = ft_strlen((char *)s2);
	newstr = (char *)malloc(n + m + 1);
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (++i < n - 1)
		newstr[i] = s1[i];
	newstr[i++] = c;
	while (i - n < m)
	{
		newstr[i] = s2[i - n];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

void ft_updatepwd(const char *prop, char *value)
{
	t_env *current;

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

int ft_cd(t_cmd *cmd)
{
	char *olddir;
	char *newdir;
	int ret;
	int len;
	char *dir;

	olddir = NULL;
	newdir = NULL;
	len = ft_len(cmd->args);
	if (len > 2)
		ft_putendl_fd(strerror(errno), STDERR_FILENO); //TODO fix error
	else if (len == 1 || (len == 2 && cmd->args[1][0] == '~'))
	{
		char *tmp1 = get_env_var("HOME");
		char *tmp2 = cmd->args[1] ? cmd->args[1] + 1 : "";
		dir = ft_strjoin(tmp1, tmp2);
		if (ft_strlen(dir) == 1)
		{
			error_handle(E_CD_HOME, 1, "");
			return (0);
		}
	}
	else
		dir = cmd->args[1];
	olddir = getcwd(olddir, 0);
	ret = chdir(dir);
	newdir = getcwd(newdir, 0);
	if (ret == 0)
	{
		ft_updatepwd("OLDPWD", olddir);
		ft_updatepwd("PWD", newdir);
	}
	else
		error_handle(E_STANDARD, 1, "cd");
	free(olddir);
	free(newdir);
	return (1);
}
