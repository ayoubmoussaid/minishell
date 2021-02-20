/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:14:06 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/20 12:20:19 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*dir;

	if (cmd->args)
		ft_putstr_fd("", STDERR_FILENO);
	dir = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
	{
		error_handle(E_STANDARD, 1, "pwd");
		return (1);
	}
	ft_putendl_fd(dir, 1);
	free(dir);
	return (0);
}
