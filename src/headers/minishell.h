/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:25:05 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/15 14:16:18 by fmehdaou         ###   ########.fr       */
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


# define COMMA 0
# define QUOTED 1
# define QUOTES 2
# define INFILE 3
# define PIPE 4





static char		*(g_mishell_err[]) =
{
	"Syntax error near unexpected token `;;' ",
	"Syntax error near unexpected token  `\"' ",
	"Syntax error near unexpected token  `\'' ",
	"Syntax error near unexpected token  `>' ",
	"Syntax error near unexpected token  `|' ",
	""
};







typedef struct	s_getl{
	char *line;
	char *line_t;
	int len;
	int fd;
	int r;
	char **sp;
	char **sps;
	int quote;//active ' " or inactive
	char *zeros;
	int err; // errors
	char c;
	int comma; // for the err ;;    ;       ;
	int pipe; // for the err || |      |
	int redirection;
	char space;

}				t_getl;


typedef struct	s_cmd{
	char			*c;
	char			**args;
	int				pipe;
	char			**files;
	int				*num_files;
}				t_cmd;



typedef struct	s_lst
{
	t_cmd			*content;
	struct s_list	*next;
}				t_lst;


typedef struct	s_shell{
	char	**env;
	FILE	*debug_file;
}				t_shell;



void	ft_env(char **env);
void	ft_pwd();
void	ft_cd(t_shell *shell, char *dir);
void	ft_echo(t_shell *shell, char **args);

#endif
