/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:24:24 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/06 10:42:48 by amoussai         ###   ########.fr       */
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
			delete_env_var(cmd->args[i]);
		else if (ret == 0)
		{
			error_handle(E_UNSET_NOTVAID, 1, cmd->args[i]);
			ex = 0;
		}
		i++;
	}
	return (ex);
}
