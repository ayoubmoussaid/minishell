/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 09:43:12 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/10 14:57:51 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


//TODO to fix
int		ft_isvalid(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && !(ft_isalpha(str[i]) || str[i] == '_'))
			return (0);
		if (i != 0 && !(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		if (i != 0 && str[i] == '=')
			break ;
	}
	return (1);
}

void	ft_export(t_shell *shell, char **args)
{
	int i;

	i = 0;
	while (args && args[i] != 0)
	{
		if (ft_isvalid(args[i]))
		{
			fprintf(shell->debug_file, "-- %s --\n", args[i]);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
			ft_putstr_fd(args[i], STDOUT_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
		}
	}
}
