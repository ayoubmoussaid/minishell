/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:30:33 by amoussai          #+#    #+#             */
/*   Updated: 2021/01/30 15:30:59 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_specialjoin(char const *s1, char const *s2, char c)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	n;
	unsigned int	m;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen((char*)s1) + 1;
	m = ft_strlen((char*)s2);
	newstr = (char*)malloc(n + m + 1);
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

void	ft_updatepwd( const char *prop, char *value)
{
	t_env	*current;

	current = g_shell->envs;
	while (g_shell->envs != NULL && current != NULL)
	{
		if (ft_strcmp(current->key, prop) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
		}
		current = current->next;
	}
}

void	ft_cd( t_cmd	*cmd)
{
	char	*olddir;
	char	*newdir;
	int		ret;
	int		len;
	char	*dir;

	olddir = NULL;
	newdir = NULL;
	len = ft_len(cmd->args);
	if (len > 2)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else if (len == 1 || (len == 2 && cmd->args[1][0] == '~'))
	{
		dir = ft_strjoin(get_env_var("HOME"), cmd->args[1] + 1);
		if (ft_strlen(dir) == 1)
		{
			ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
			exit(0);
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
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	free(olddir);
	free(newdir);
}


