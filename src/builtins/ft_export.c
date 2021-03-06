/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 09:43:12 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 15:37:17 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	export_no_args(void)
{
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

void	norm_export(t_cmd *cmd, int *ex, int *i)
{
	int		index;
	int		ret;
	char	*value;
	char	*key;

	index = ft_str_index(cmd->args[*i], '=');
	ret = ft_isvalid(cmd->args[*i]);
	if (ret == 1)
	{
		key = ft_substr(cmd->args[*i], 0, index);
		if (index == -1)
			value = NULL;
		else
			value = ft_substr(cmd->args[*i],
				index + 1, ft_strlen(cmd->args[*i]));
		add_env_var(create_new_var(key, value));
		free(key);
		free(value);
	}
	else if (ret == 0)
	{
		error_handle(E_EXPORT_NOTVAID, 1, cmd->args[*i]);
		*ex = 1;
	}
	(*i)++;
}

int		ft_export(t_cmd *cmd)
{
	int		i;
	int		ex;

	i = 1;
	ex = 0;
	while (cmd->args && cmd->args[i] != 0)
		norm_export(cmd, &ex, &i);
	if (cmd->args[1] == NULL)
		export_no_args();
	return (ex);
}
