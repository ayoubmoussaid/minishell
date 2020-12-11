/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:25:05 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/11 10:33:28 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include "../../libft/libft.h"
#include "../../gnl/get_next_line.h"


typedef struct	s_shell{
	char	**env;
	FILE	*debug_file;
}				t_shell;

void	ft_env(char **env);
void	ft_pwd();
void	ft_cd(t_shell *shell, char *dir);
void	ft_echo(t_shell *shell, char **args);
void	ft_export(t_shell *shell, char **args);
char	*ft_getvar(t_shell *shell, char *search);

#endif
