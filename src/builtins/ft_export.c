/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 09:43:12 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/22 09:23:45 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_export(t_shell *shell, char **args)
{
	int		i;
	int		ret;
	t_env	*new;
	char	*key;
	char	*value;
	int		index;

	i = 0;
	while (args && args[i] != 0)
	{
		index = ft_str_index(args[i], '=');
		ret = ft_isvalid(args[i]);
		if (ret == 1)
		{
			//fprintf(shell->debug_file, "-- %s --\n", args[i]);
			key = ft_substr(args[i], 0, index);
			value = ft_substr(args[i], index + 1, ft_strlen(args[i]));
			new = create_new_var(key, value);
			add_env_var(shell, new);
			free(key);
			free(value);
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
