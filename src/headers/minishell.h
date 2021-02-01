/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:25:05 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/01 16:20:23 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../../libft/libft.h"
#include "../../gnl/get_next_line.h"


# define READ 0
# define WRITE 1


typedef struct  s_env{
	struct s_env    *next;
	char            *key;
	char            *value;
	//char			*full;
}				t_env;


typedef struct  s_files{
	struct s_files	*next;
	char			*name;
	char			type;
}               t_files;

typedef struct  s_cmd{
	struct s_cmd    *next;
	char			*c;
	char			*executable;
	char			**args;
	t_files			*files;
	int				fdr;
	int				fdw;
}               t_cmd;

typedef struct  s_pipeline
{
	struct s_pipeline	*next;
	t_cmd				*pipe;
}               t_pipeline;

typedef struct	s_shell{
	int				exit_status;
	char			*line;
	//char			**splitted;
	t_env			*envs;
	FILE			*debug_file;
	t_pipeline		*pipeline;
	t_cmd			*cmd;
}				t_shell;


t_shell *g_shell;
// # define ECHO 0
// # define PWD 1
// # define ENV 2
// # define EXPORT 3
// # define UNSET 4
// # define EXIT 5

void	ft_env(t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
void	ft_cd(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_export(t_cmd	*cmd);
void	ft_unset(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);


int		ft_len(char **tab);
int		ft_isvalid(char *str);
int		ft_isvalid_unset(char *str);

t_env	*create_new_var(char *key, char *value);
char	*get_env_var( char *key);
void	delete_env_var( char *key);
void	add_env_var(t_env *new);
void	free_env_var(t_env	*del);
void	print_env();
int		ft_str_index(char *str, char c);
void	my_env(char **env);
char	*ft_specialjoin(char const *s1, char const *s2, char c);

#endif
