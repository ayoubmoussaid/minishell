/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:25:05 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/28 12:24:37 by amoussai         ###   ########.fr       */
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
	struct s_env    *next;
	char            *key;
	char            *value;
	//char			*full;
}				t_env;


typedef struct  s_files{
	struct s_files *next;
	char    *file;
	char    type;
}               t_files;

typedef struct  s_cmd{
	struct s_cmd    *next;
	char			*c;
	char			**args;
	int 			pipe;
	int				prepipe;
	t_files			*files;
}               t_cmd;

typedef struct	s_shell{
	t_env			*envs;
	FILE			*debug_file;
	t_cmd			*cmd;
}				t_shell;

// typedef struct  s_lst
// {
// 	t_cmd			*content;
// 	struct s_list	*next;
// }               t_lst;

// # define ECHO 0
// # define PWD 1
// # define ENV 2
// # define EXPORT 3
// # define UNSET 4
// # define EXIT 5

//char	*g_builtins[6] = {"echo", "pwd", "env", "export", "unset", "exit"};

void	ft_env(t_env *env);
void	ft_pwd();
void	ft_cd(t_shell *shell, char *dir);
void	ft_echo(t_shell *shell, char **args);
void	ft_export(t_shell *shell, char **args);
void	ft_unset(t_shell *shell, char **args);
void	ft_exit();

//void 	(*g_functions[6]) = {&ft_echo, &ft_pwd, &ft_env, &ft_export, &ft_unset, &ft_exit};

int		ft_len(char **tab);
int		ft_isvalid(char *str);
int		ft_isvalid_unset(char *str);

t_env	*create_new_var(char *key, char *value);
char	*get_env_var(t_shell *shell, char *key);
void	delete_env_var(t_shell *shell, char *key);
void	add_env_var(t_shell *shell, t_env *new);
void	free_env_var(t_env	*del);
void	print_env(t_shell *shell);
int		ft_str_index(char *str, char c);
void	my_env(char **env, t_shell *shell);

#endif
