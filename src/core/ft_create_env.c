/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 09:21:05 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/24 08:26:46 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		ft_str_index(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	my_env(char **env, t_shell *shell)
{
	int		j;
	t_env	*elt;
	char	*key;
	char	*value;
	int		index;

	j = 0;
	
	while (env[j] != NULL)
	{
		if ((index = ft_str_index(env[j], '=')) != -1)
		{
			key = ft_substr(env[j], 0, index);
			value = ft_substr(env[j], index + 1, ft_strlen(env[j]));
			elt = create_new_var(key, value);
			add_env_var(shell, elt);
			free(key);
			free(value);
		}
		j++;
	}
}
