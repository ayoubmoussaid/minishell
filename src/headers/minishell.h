/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:25:05 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/17 13:56:57 by amoussai         ###   ########.fr       */
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

typedef struct  s_env{
	char            *key;
	char            *value;
	struct s_env    *next;
}				t_env;

typedef struct	s_shell{
	t_env			*envs;
	char			**env;
	FILE			*debug_file;
}				t_shell;

typedef struct  s_files{
	char    *file;
	char    type;
}               t_files;

typedef struct  s_cmd{
	char			*c;
	char			**args;
	int 			pipe;
	t_files			*files;
	struct s_cmd    *next;
}               t_cmd;
typedef struct  s_lst
{
	t_cmd			*content;
	struct s_list	*next;
}               t_lst;

void	ft_env(char **env);
void	ft_pwd();
void	ft_cd(t_shell *shell, char *dir);
void	ft_echo(t_shell *shell, char **args);
void	ft_export(t_shell *shell, char **args);
void	ft_unset(t_shell *shell, char **args);
void	ft_exit();
char	*ft_getvar(t_shell *shell, char *search);
int		ft_len(char **tab);
void	ft_addvar(t_shell *shell, char *var);
int		ft_isvalid(char *str);
int		ft_isvalid_unset(char *str);
void	ft_deletevar(t_shell *shell, char *search);

#endif
