/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 09:43:12 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/15 10:48:57 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_export(t_shell *shell, char **args)
{
	int i;
	int ret;

	i = 0;
	while (args && args[i] != 0)
	{
		ret = ft_isvalid(args[i]);
		if (ret == 1)
		{
			//fprintf(shell->debug_file, "-- %s --\n", args[i]);
			ft_addvar(shell, args[i]);
		}
		else if (ret == 0)
		{
			ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
			ft_putstr_fd(args[i], STDOUT_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
		}
		i++;
	}
}