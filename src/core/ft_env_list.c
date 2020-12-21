/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:03:37 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/21 10:28:20 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_env_var(t_env *del)
{
	free(del->key);
	free(del->value);
	free(del);
}

t_env	*create_new_var(char *key, char *value)
{
	t_env	*env;

	env = (t_env*)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	return (env);
}

void	add_env_var(t_shell *shell, t_env *new)
{
	t_env	*current;
	t_env	*tobefreed;

	if (shell->envs && *(shell->envs))
	{
		current = *(shell->envs);
		if (ft_strcmp(current->key, new->key) == 0)
		{
			new->next = current->next;
			*(shell->envs) = new;
			free_env_var(current);
			return ;
		}
		while (current->next != NULL &&
			ft_strcmp(current->next->key, new->key) != 0)
			current = current->next;
		if (current->next == NULL)
			current->next = new;
		else
		{
			new->next = current->next->next;
			tobefreed = current->next;
			current->next = new;
			free_env_var(tobefreed);
		}
	}
	else
		*(shell->envs) = new;
}


void	delete_env_var(t_shell *shell, char *key)
{
	t_env	*current;
	t_env	*tobefreed;

	if (shell->envs && *(shell->envs))
	{
		current = *(shell->envs);
		if (ft_strcmp(current->key, key) == 0)
		{
			*(shell->envs) = current->next;
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

char	*get_env_var(t_shell *shell, char *key)
{
	t_env	*current;

	if (shell->envs && *(shell->envs))
	{
		current = *(shell->envs);
		while (current != NULL && ft_strcmp(current->key, key) != 0)
			current = current->next;
		if (current == NULL)
			return (ft_strdup(""));
		return (current->value);
	}
	return (ft_strdup(""));
}

void	print_env(t_shell *shell)
{
	t_env	*current;

	if (shell->envs && *(shell->envs))
	{
		current = *(shell->envs);
		while (current != NULL)
		{
			fprintf(shell->debug_file, "|%s|=|%s|\n", current->key, current->value);
			current = current->next;
		}
	}
}
