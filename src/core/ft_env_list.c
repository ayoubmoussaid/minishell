/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:03:37 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 19:13:13 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_env	*create_new_var(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = value ? ft_strdup(value) : NULL;
	env->next = NULL;
	return (env);
}

void	norm_add_env_var(t_env *new)
{
	t_env	*current;

	current = g_shell->envs;
	if (ft_strcmp(current->key, new->key) == 0)
	{
		free(current->value);
		current->value = new->value ? ft_strdup(new->value) : NULL;
		free_env_var(new);
		return ;
	}
	while (current->next != NULL &&
		ft_strcmp(current->next->key, new->key) != 0)
		current = current->next;
	if (current->next == NULL)
		current->next = new;
	else
	{
		if (new->value)
		{
			free(current->next->value);
			current->next->value = new->value ? ft_strdup(new->value) : NULL;
		}
		free_env_var(new);
	}
}

void	add_env_var(t_env *new)
{
	if (g_shell->envs)
		norm_add_env_var(new);
	else
		g_shell->envs = new;
}

void	delete_env_var(char *key)
{
	t_env *current;
	t_env *tobefreed;

	if (g_shell->envs)
	{
		current = g_shell->envs;
		if (ft_strcmp(current->key, key) == 0)
		{
			g_shell->envs = current->next;
			free_env_var(current);
			return ;
		}
		while (current->next != NULL &&
			ft_strcmp(current->next->key, key) != 0)
			current = current->next;
		if (current->next != NULL)
		{
			tobefreed = current->next;
			current->next = current->next->next;
			free_env_var(tobefreed);
		}
	}
}

char	*get_env_var(char *key)
{
	t_env *current;

	if (g_shell->envs)
	{
		current = g_shell->envs;
		while (current != NULL && ft_strcmp(current->key, key) != 0)
			current = current->next;
		if (current != NULL)
			return (ft_strdup(current->value ? current->value : ""));
	}
	return (ft_strdup(""));
}
