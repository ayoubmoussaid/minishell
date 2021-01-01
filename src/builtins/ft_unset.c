/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:24:24 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/22 09:16:25 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_unset(t_shell *shell, char **args)
{
	int i;
	int ret;

	i = 0;
	while (args && args[i] != 0)
	{
		ret = ft_isvalid_unset(args[i]);
		if (ret == 1)
		{
			//fprintf(shell->debug_file, "-- %s --\n", args[i]);
			delete_env_var(shell, args[i]);
		}
		else if (ret == 0)
		{
			ft_putstr_fd("minishell: unset: `", STDOUT_FILENO);
			ft_putstr_fd(args[i], STDOUT_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
		}
		i++;
	}
}
