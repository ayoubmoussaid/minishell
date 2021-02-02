/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:24:24 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/02 11:31:04 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_unset(t_cmd *cmd)
{
	int i;
	int ret;
	int ex;

	ex = 1;
	i = 0;
	while (cmd->args && cmd->args[i] != 0)
	{
		ret = ft_isvalid_unset(cmd->args[i]);
		if (ret == 1)
		{
			delete_env_var(cmd->args[i]);
		}
		else if (ret == 0)
		{
			ft_putstr_fd("minishell: unset: `", STDOUT_FILENO);
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
			ex = 0;
		}
		i++;
	}
	return (ex);
}
