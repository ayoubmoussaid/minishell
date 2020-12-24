/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:30:33 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/24 10:36:54 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_specialjoin(char const *s1, char const *s2)
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
	newstr[i++] = '=';
	while (i - n < m)
	{
		newstr[i] = s2[i - n];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

void	ft_updatepwd(t_shell *shell, const char *prop, char *value)
{
	t_env	*current;

	current = shell->envs;
	while (shell->envs != NULL && current != NULL)
	{
		if (ft_strcmp(current->key, prop) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			//fprintf(shell->debug_file, "-- %s=%s --\n", current->key, current->value);
		}
		current = current->next;
	}
}

void	ft_cd(t_shell *shell, char *dir)
{
	char	*olddir;
	char	*newdir;
	int		ret;

	olddir = NULL;
	newdir = NULL;
	olddir = getcwd(olddir, 0);
	ret = chdir(dir);
	newdir = getcwd(newdir, 0);
	if (ret == 0)
	{
		ft_updatepwd(shell, "OLDPWD", olddir);
		ft_updatepwd(shell, "PWD", newdir);
	}
	else
		ft_putendl_fd(strerror(errno), STDOUT_FILENO);
	free(olddir);
	free(newdir);
}


