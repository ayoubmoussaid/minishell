/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:24:53 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 15:12:46 by amoussai         ###   ########.fr       */
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
			ft_putchar_fd(*s, fd);
		s++;
	}
}

int		verify_echo_n(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if ((i == 0 && str[i] != '-') || (i != 0 && str[i] != 'n'))
			return (0);
		i++;
	}
	return (1);
}

int		ft_echo(t_cmd *cmd)
{
	int i;
	int char_count;

	char_count = 1;
	i = 0;
	if (!cmd->args)
		ft_putendl_fd("", STDOUT_FILENO);
	else if (ft_len(cmd->args) == 1)
		write(STDOUT_FILENO, "\n", 1);
	else
	{
		while (cmd->args[++i] && verify_echo_n(cmd->args[i]))
			char_count = 0;
		while (cmd->args[i] != NULL)
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			if (cmd->args[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
		write(STDOUT_FILENO, "\n", char_count);
	}
	return (0);
}
