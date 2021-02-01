/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:25:05 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/01 17:31:34 by fmehdaou         ###   ########.fr       */
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
# define COMMA 0
# define QUOTED 1
# define QUOTES 2
# define INFILE 3
# define PIPE 4
# define COMMAD 5
#define RED 6
#define INFILED 7
#define OUTFILE 8





static char		*(g_mishell_err[]) =
{
	"Syntax error near unexpected token `;' ",
	"Syntax error near unexpected token  `\"' ",
	"Syntax error near unexpected token  `\'' ",
	"Syntax error near unexpected token  `>' ",
	"Syntax error near unexpected token  `|' ",
	"Syntax error near unexpected token `;;'",
	"syntax error near unexpected token `newline'",
	"Syntax error near unexpected token  `>>' ",
	"Syntax error near unexpected token  `<' ",
	""
};


typedef struct	s_getl{
	char	*line;
	int 	i;
	int 	s_quote;
	int 	d_quote;
	int 	dollar;
	char 	*l;
	int		semicolon; //;
	int 	red_in; // >
	int 	red_out; // <
	int 	append; // >>
	int		pipe;
	int		brake;
	char	**sp_c; // split with semicolone
	char	**sp_p; //split with pipe
	char 	**sp_re; // split with redirection

	
	
}				t_getl;


typedef struct  s_env{
    struct s_env    *next;
    char            *key;
    char            *value;
    //char          *full;
}               t_env;



typedef struct  s_files{
    struct s_files  *next;
    char            *name;
    char            type; // > < a
}               t_files;


typedef struct  s_cmd{
	struct s_cmd    *next;
    char            *c;
    char            *executable;
    char            **args;
    t_files         *files;
	int				fdr;
	int				fdw;
}               t_cmd;



typedef struct  s_pipeline
{
	struct s_pipeline   *next;
    t_cmd               *pipe;
}               t_pipeline;

typedef struct	s_shell{
	int				exit_status;
	char			*line;
	//char			**splitted;
	t_env			*envs;
	FILE			*debug_file;
	t_pipeline		*head;
	t_cmd			*cmd;
}				t_shell;


t_shell *g_shell;


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

void	flip_line();
char	*reflip(char *str);
void	do_the_work(char **env);
void	execute();
void	parse_line(t_getl *getl, t_shell *shell);

#endif
