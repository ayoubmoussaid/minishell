/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_needs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:49:30 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 19:58:14 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		get_index_of_separator(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
			break ;
		i++;
	}
	return (i);
}

void	override_str(char **str, int index)
{
	while ((*str)[index] != '\0')
	{
		(*str)[index] = (*str)[index + 1];
		index++;
	}
}

int		check_for_simple_double(char **line, int *i, int *s, int *d)
{
	int x;

	x = 0;
	if ((*line)[*i] == '\"' && *s == 0)
	{
		override_str(line, *i);
		*d = !(*d);
		x = 1;
	}
	if ((*line)[*i] == '\'' && *d == 0)
	{
		override_str(line, *i);
		(*s) = !(*s);
		if (*s == 0)
			(*i)--;
		x = 1;
	}
	return (x);
}

int		check_for_after_backslash(char c)
{
	return (c == '$' || c == '\"' || c == '\\');
}
