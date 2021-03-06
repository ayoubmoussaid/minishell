/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:48:17 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 19:32:53 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	hard_coded(char **tmp1, char **line, char **tmp2)
{
	*tmp2 = ft_strjoin((*line), *tmp1);
	free(*tmp1);
	free(*line);
	(*line) = *tmp2;
}

void	variable_expansion(int *i, char **line, int d, int s)
{
	char	*tmp1;
	char	*tmp2;
	int		index;

	index = 1;
	if ((*line)[*i + 1] == '?')
		tmp2 = ft_itoa(g_shell->exit_status);
	else
	{
		index = get_index_of_separator((*line) + (*i) + 1);
		tmp1 = ft_substr((*line) + (*i) + 1, 0, index);
		tmp2 = get_env_var(tmp1);
		free(tmp1);
	}
	if (index != 0 || (index == 0 && d == 0 && s == 0 &&
		((*line)[(*i) + 1] == '\'' || (*line)[(*i) + 1] == '\"')))
	{
		tmp1 = ft_strjoin(tmp2, (*line) + (*i) + index + 1);
		free(tmp2);
		(*line)[*i] = '\0';
		hard_coded(&tmp1, line, &tmp2);
		((*line)[*i] == '\"' || (*line)[*i] == '\'') ? (*i)-- : 1;
	}
	else
		free(tmp2);
}

void	flip_line(char **line)
{
	int		i;
	int		d;
	int		s;

	i = -1;
	d = 0;
	s = 0;
	while ((*line)[++i] != '\0')
	{
		while (check_for_simple_double(line, &i, &s, &d))
		{
		}
		if ((*line)[i] == '$' && s == 0)
			variable_expansion(&i, line, d, s);
		if (d == 1 && (*line)[i] == '\\' &&
			check_for_after_backslash((*line)[i + 1]))
			override_str(line, i);
		if ((d || s) && (*line)[i] > 0)
			(*line)[i] = -(*line)[i];
	}
}
