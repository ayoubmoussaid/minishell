/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:24:53 by amoussai          #+#    #+#             */
/*   Updated: 2021/01/01 12:12:33 by amoussai         ###   ########.fr       */
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

void	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		char_count;
	char	*str;

	char_count = 1;
	i = 0;
	if (!cmd->args)
		ft_putendl_fd("", STDOUT_FILENO);
	else
	{
		if (ft_strcmp(cmd->args[1], "-n") == 0)
		{
			cmd->args++;
			char_count = 0;
		}
		while (cmd->args[++i] != NULL)
		{
			if (cmd->args[i][0] == '$')
			{
				str = get_env_var(shell, &cmd->args[i][1]);
				ft_putstr_fd(str, STDOUT_FILENO);
				if (ft_strlen(str) != 0 && cmd->args[i + 1] != NULL)
					ft_putstr_fd(" ", STDOUT_FILENO);
				free(str);
			}
			else
			{
				ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
				if (cmd->args[i + 1] != NULL)
					ft_putstr_fd(" ", STDOUT_FILENO);
			}
		}
		write(STDOUT_FILENO, "\n", char_count);
	}
}
