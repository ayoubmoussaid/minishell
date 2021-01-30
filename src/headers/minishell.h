/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:25:05 by amoussai          #+#    #+#             */
/*   Updated: 2021/01/30 15:02:41 by fmehdaou         ###   ########.fr       */
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
  
    char            *c;
    char            *executable;
    char            **args;
    t_files         *files;
	struct s_cmd    *next;
}               t_cmd;



typedef struct  s_pipeline
{
    t_cmd               *pipe;
	struct s_pipeline   *next;

}               t_pipeline;



typedef struct  s_shell{
    t_env           *envs;
    FILE            *debug_file;
    t_pipeline      *head;
}      			t_shell;

void	ft_env(t_env *env);
void	ft_pwd();
void	ft_cd(t_shell *shell, char *dir);
void	ft_echo(t_shell *shell, char **args);
void	ft_export(t_shell *shell, char **args);
void	ft_unset(t_shell *shell, char **args);
void	ft_exit();

//void 	(*g_functions[]) = {&ft_echo, &ft_pwd, &ft_env, &ft_export, &ft_unset, &ft_exit};

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
char	*ft_specialjoin(char const *s1, char const *s2, char c);


#endif
