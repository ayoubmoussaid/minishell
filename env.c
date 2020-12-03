/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:12 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/03 14:33:17 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(char *env){
	int i = 0;
	while(env[i] != '\0'){
		if(env[i] == ';')
			ft_putchar_fd('\n', STDOUT_FILENO);
		else
			ft_putchar_fd(env[i], STDOUT_FILENO);
	}
}