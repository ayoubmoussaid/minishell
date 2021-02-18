/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 09:43:12 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/06 10:39:19 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	export_no_args(void){
	t_env *current;

	current = g_shell->envs;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		if (current->value != NULL)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

int		ft_export(t_cmd *cmd)
{
	int		i;
	int		ret;
	t_env	*new;
	char	*key;
	char	*value;
	int		index;
	int		ex;

	i = 1;
	ex = 1;
	while (cmd->args && cmd->args[i] != 0)
	{
		index = ft_str_index(cmd->args[i], '=');
		ret = ft_isvalid(cmd->args[i]);
		if (ret == 1)
		{
			key = ft_substr(cmd->args[i], 0, index);
			if (index == -1)
				value = NULL;
			else
				value = ft_substr(cmd->args[i], index + 1, ft_strlen(cmd->args[i]));
			new = create_new_var(key, value);
			add_env_var(new);
			free(key);
			free(value);
		}
		else if (ret == 0)
		{
			error_handle(E_EXPORT_NOTVAID, 1, cmd->args[i]);
			ex = 0;
		}
		i++;
	}
	if (cmd->args[1] == NULL)
		export_no_args();
	return (ex);
}
