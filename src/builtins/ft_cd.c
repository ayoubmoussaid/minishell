/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:30:33 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/05 13:21:06 by amoussai         ###   ########.fr       */
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
	newstr[i] = '=';
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
	int i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strcmp(ft_substr(shell->env[i], 0, ft_strlen(prop)), prop) == 0)
		{
			free(shell->env[i]);
			printf("%s=%s\n", prop, value);
			shell->env[i] = ft_specialjoin(prop, value);
			printf("-- %s --\n", shell->env[i]);
		}
		i++;
	}
}

void	ft_cd(t_shell *shell, char *dir)
{
	char	*olddir;
	int		ret;

	olddir = NULL;
	olddir = getcwd(olddir, 0);
	ret = chdir(dir);
	if (ret == 0)
	{
		ft_updatepwd(shell, "OLDPWD", olddir);
		ft_updatepwd(shell, "PWD", dir);
	}
	else
		ft_putendl_fd(strerror(errno), STDOUT_FILENO);
	free(olddir);
	//free(dir);
}


