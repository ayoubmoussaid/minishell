/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 10:27:31 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/05 11:33:01 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int		ft_isvalid(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[0] == '_' && str[1] == '=')
			return (2);
		if (i != 0 && str[i] == '=')
			break ;
		if (i == 0 && !(ft_isalpha(str[i]) || str[i] == '_'))
			return (0);
		if (i != 0 && !(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int		ft_isvalid_unset(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[0] == '_' && str[1] == '=')
			return (2);
		if (i == 0 && !(ft_isalpha(str[i]) || str[i] == '_'))
			return (0);
		if (i != 0 && !(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
