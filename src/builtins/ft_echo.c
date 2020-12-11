/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:24:53 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/11 10:32:22 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"



void	ft_specialprint(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		if (*s == '\\' && *(s + 1) == '\\')
			ft_putchar_fd(*s, fd);
		else if (*s != '\\')
		{
			ft_putchar_fd(*s, fd);
		}
		s++;
	}
}

//TODO check backslash
void	ft_echo(t_shell *shell, char *args[])
{
	int		i;
	int		char_count;
	char	*str;

	char_count = 1;
	i = -1;
	if (!args)
		ft_putendl_fd("", STDOUT_FILENO);
	else
	{
		if (ft_strcmp(args[0], "-n") == 0)
		{
			args++;
			char_count = 0;
		}
		while (args[++i] != NULL)
		{
			if (args[i][0] == '$')
			{
				str = ft_getvar(shell, &args[i][1]);
				ft_putstr_fd(str, STDOUT_FILENO);
				if (ft_strlen(str) != 0 && args[i + 1] != NULL)
					ft_putstr_fd(" ", STDOUT_FILENO);
				free(str);
			}
			else
			{
				ft_putstr_fd(args[i], STDOUT_FILENO);
				if (args[i + 1] != NULL)
					ft_putstr_fd(" ", STDOUT_FILENO);
			}
		}
		write(STDOUT_FILENO, "\n", char_count);
	}
}
