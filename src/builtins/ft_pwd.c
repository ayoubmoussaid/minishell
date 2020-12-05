/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:14:06 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/05 12:24:13 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_pwd()
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	ft_putendl_fd(dir, 1);
	free(dir);
}
