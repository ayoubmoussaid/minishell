/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:25:05 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/07 07:54:02 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../../libft/libft.h"
# include "../../gnl/get_next_line.h"

# define E_CNF 0
# define E_STANDARD 1
# define E_TMA 4
# define E_CD_NOFOD 5
# define E_CD_HOME 6
# define E_EXPORT_NOTVAID 7
# define E_UNSET_NOTVAID 8
# define E_WPATH 9
# define E_ISDIR 10
# define E_EXIT_ARG 11
# define E_SYNTAX 12

# define READ 0
# define WRITE 1
# define COMMA 0
# define QUOTED 1
# define QUOTES 2
# define INFILE 3
# define PIPE 4
# define COMMAD 5
# define RED 6
# define INFILED 7
# define OUTFILE 8

typedef struct		s_get_file{
	int				save;
	char			*tmp2;
	char			*tmp;
	char			*tmp1;
	int				index_s;
	int				index_e;
}					t_get_file;

typedef struct		s_getl
{
	char			*line;
	int				i;
	int				s_quote;
	int				d_quote;
	int				dollar;
	char			*l;
	int				semicolon;
	int				red_in;
	int				red_out;
	int				append;
	int				pipe;
	int				brake;
	char			**sp_c;
	char			**sp_p;
	char			**sp_re;
}					t_getl;

typedef struct		s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}					t_env;

typedef struct		s_files
{
	struct s_files	*next;
	char			*name;
	char			type;
}					t_files;

typedef struct		s_cmd
{
	struct s_cmd	*next;
	char			*c;
	char			*executable;
	char			**args;
	t_files			*files;
	int				fdr;
	int				fdw;
	pid_t			pid;
}					t_cmd;

typedef struct		s_shell
{
	int				exit_status;
	t_env			*envs;
	t_cmd			*cmd;
}					t_shell;

static char	*g_builtins[] = {"echo", "pwd", "cd", "env",
	"export", "unset", "exit", (void *)0};
t_shell		*g_shell;
t_getl		*g_getl;
pid_t		g_pid;
int			g_simple_cmd;

static char	*(g_mishell_err[]) =
{
	"syntax error near unexpected token `;' ",
	"syntax error near unexpected token  `\"' ",
	"syntax error near unexpected token  `\'' ",
	"syntax error near unexpected token  `>' ",
	"syntax error near unexpected token  `|' ",
	"syntax error near unexpected token `;;'",
	"syntax error near unexpected token `newline'",
	"syntax error near unexpected token  `>>' ",
	"syntax error near unexpected token  `<' ",
	""
};

int					ft_env(t_cmd *cmd);
int					ft_pwd(t_cmd *cmd);
int					ft_cd(t_cmd *cmd);
int					ft_echo(t_cmd *cmd);
int					ft_export(t_cmd *cmd);
int					ft_unset(t_cmd *cmd);
int					ft_exit(t_cmd *cmd);
int					ft_len(char **tab);
int					ft_isvalid(char *str);
int					ft_isvalid_unset(char *str);
t_env				*create_new_var(char *key, char *value);
char				*get_env_var(char *key);
void				delete_env_var(char *key);
void				add_env_var(t_env *new);
void				free_env_var(t_env *del);
void				print_env();
int					ft_str_index(char *str, char c);
void				my_env(char **env);
char				*ft_specialjoin(char const *s1, char const *s2, char c);
void				free_env_var(t_env *del);
void				flip_line(char **line);
void				do_the_work(char **env);
void				execute();
void				parse_line(t_getl *g_getl);
void				get_command(t_getl *g_getl);
void				errrors(char *err);
void				init_state(t_getl *g_getl);
int					is_special_char(char c);
int					is_all_off(t_getl *g_getl);
int					is_on(t_getl *g_getl);
void				signal_handler(int sig);
int					parse_files(t_cmd *cmd);
void				dup_close(int fd1, int fd2);
int					prepare_fd(t_cmd *cmd, int p[2], int std[2]);
void				finish_fd(t_cmd *cmd, int p[2], int std[2]);
char				**get_env(t_env *env);
int					get_real_cmd(t_cmd *cmd, int *index);
int					error_handle(int err, int exit_code, char *need);
void				ft_free(char **str);
void				ft_clear_files_list(t_cmd *cmd);
void				ft_clear_cmd_list(void);
void				ft_find_file(char **str, t_cmd *cmd);
void				add_file_to_list(t_cmd *cmd, t_files *file);
char				*get_file_name(char **str, int *index, int count);
int					verify_final(t_getl *g_getl);
int					verify_s_pipe(t_getl *g_getl, int *i);
int					verify_s_red(t_getl *g_getl, int *i);
int					verify_s_red_out(t_getl *g_getl, int *i);
void				verify_rest(t_getl *g_getl, int *i);
void				verify_s_quote(t_getl *g_getl);
int					verify_d_quote(t_getl *g_getl);
int					quote_handler(t_getl *g_getl, char c);
int					verify_s_semicolon(t_getl *g_getl, int *i);
void				verify_space(t_getl *g_getl, int *i);
int					get_index_of_separator(char *str);
void				override_str(char **str, int index);
int					check_for_simple_double(char **line,
	int *i, int *s, int *d);
int					check_for_after_backslash(char c);

#endif
