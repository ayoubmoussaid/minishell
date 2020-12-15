/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/15 14:29:29 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void	fct(int num)
{
	exit(0);
	printf("processus fils est terminé ! , %d.\n", num);
}


void	my_env(char **env, t_shell *shell)
{
	int i;
	int j;

	i = 0;
	while (env[i] != NULL)
		i++;
	shell->env = (char**)malloc(sizeof(char*) * (i + 1));
	
	j = 0;
	while (j < i)
	{
		shell->env[j] = ft_strdup(env[j]);
		j++;
	}
	shell->env[j] = NULL;
}



void	printsp(char **sp)
{
	int i = -1;

	printf("--------start--------\n");
	while(sp[++i])
		printf("|%s|\n",sp[i]);
	printf("---------end---------\n");
}


// int	check_comma(t_getl *getl)
// {
// 	int i;
// 	int sq;
// 	int dq;

// 	i = -1;
// 	dq = 34;
// 	sq = 39;

// 	while(getl->line[++i])
// 	{
// 		if (getl->line[i] == ';')
// 		{
// 			if ((getl->line[i - 1] == (char)dq && getl->line[i + 1] == (char)dq) || 
// 			(getl->line[i - 1] == (char)sq && getl->line[i + 1] == (char)sq))
// 				return (1);
// 		}
// 	}
// 	return (0);
// }


int indexof_char(char *str, char *c)
{
	int i;
	char *s;

	i = -1;
	s = ft_strtrim(str, c);
	while(s[++i])
	{
		if (s[i] == c[0])
			return (i);
	}
	return (-1);
}

int skip_char(char *s, char *c, int start)
{
	int i;

	i = start;
	while(s[i])
	{
		if (s[i] == c[0] && s[i + 1] != c[0])
			return (i + 1);
		i++;
	}
	return (-1);
}









void	foreach_cmd(char *sp)
{
	
	t_cmd *cmd;
	char *s;
	int i;
	
	//char *args;
	//int in;
	
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	s = ft_strtrim(sp, " ");
//	printf("|%s|\n",s);
	cmd->c = ft_substr(s, 0, (i = indexof_char(s, " ")));
	printf("\n\n|%s|\n", cmd->c);
	// //printf("\n\nin:%d \n\n",in);
	// in = skip_char(sp, " ", in);
	// //printf("\n\n\n\nin:%d endofargs:%lu\n\n\n\n",in, ft_strlen(sp) - in);
	// args = ft_substr(sp, in, ft_strlen(sp) - in);
	//printf("|cmd->c:|%s|\n|args:|%s|\n\n",cmd->c, args);
	

	
	

}




void	get_cmd(t_getl *getl)
{
	int i;

	i = -1;
	getl->sp = ft_split(getl->line, ';');
	while(getl->sp[++i])
		foreach_cmd(getl->sp[i]);
	

	
	
	
}


void	errrors(char *err)
{
	ft_putendl_fd(err, 1);
}



int	check_comma(t_getl *getl, int *i, char c)
{
	while(getl->line[++(*i)])
	{
		if (getl->line[*i] == ';')
		{
			getl->zeros[*i] = '1'; //;
			getl->line[*i] = '1'; //;
		}
		else if (getl->line[*i] == c)
		{
			getl->quote = 0;
			return (*i);
		}
	}
	return (-1);
}




void	tozeros(char *s, int len)
{
	s[len] = '\0';
	while(--len > -1)
		*s++ =  '0';
} 



int	check_syntax(t_getl *getl,int *j, char c)
{
	int i;
	int res;

	i = *j;
	res = 0;
	getl->space = ' ';
	if (getl->line[getl->len-1] == c && c != ';')
		return (1);
	while(getl->line[++i])
	{
		if (c == '>' || c == '|')
			i++;
		if (getl->line[i] == c)
			return (1); 
		while(getl->line[i] && getl->line[i] != c)
		{
			if (getl->line[i] != ' ')
				return (0);
			i++;
		}
		res = (getl->space == ' ') ? 1 : 0;
	}
	return (res); // no err found
}








int	toclear(t_getl *getl)
{
	int i;

	getl->quote = 0;
	i = -1;
	while(getl->line[++i])
	{
		if (getl->line[i] == ';')
			if (check_syntax(getl, &i, ';'))
				return(COMMA);
		if (getl->line[i] == '>')
			if (check_syntax(getl, &i, '>'))
				return(INFILE);
		if (getl->line[i] == '|')
			if (check_syntax(getl, &i, '|'))
				return(PIPE);
		if (getl->line[i] == (char)34 || getl->line[i] == (char)39)
		{
			getl->c = (getl->line[i] == (char)34) ? (char)34 : (char)39;
			getl->quote = 1;
			i = check_comma(getl, &i, getl->c);
		}
		if (getl->quote == 1)
			return (QUOTED);// failed		
	}
	return (-1); // nothing happed
}






int     main(int argc, char **argv, char **env)
{
	t_shell *shell;
	t_getl *getl;


	//t_lst list;

	shell = (t_shell*)malloc(sizeof(t_shell));
	getl = (t_getl*)malloc(sizeof(t_getl));
	getl->err = 1;

	shell->debug_file = fopen("debug.txt", "w");
	if (argc > 1)
		argv = NULL;
	my_env(env, shell);
	//ft_env(shell.env);
	// ft_pwd();
	//ft_cd(&shell, "..");
	//ft_cd(&shell, "minishell");
	//ft_cd(&shell, "/freak");
	//fprintf(shell->debug_file, "hi fatima %d\n", 22);
	// char *tab[] = {"$OLDPWD", (void*)0};
	// ft_echo(shell, tab);



	while (1)
	{
		ft_putstr_fd("\033[92mminishell$> \033[39m", 1);
		if (get_next_line(0, &getl->line_t) > 0)
		{
			getl->line = ft_strtrim(getl->line_t, " ");
			getl->len = ft_strlen(getl->line);
			getl->zeros = (char*)malloc(sizeof(char) * (getl->len + 1));
			tozeros(getl->zeros, getl->len);
			printf("|%s|\n\n\n\n",getl->zeros);
			if ((getl->err = toclear(getl)) != -1)
			{
				errrors(g_mishell_err[getl->err]);
				continue;
			}
			get_cmd(getl);
			//printf("|%s|\n\n\n\n",getl->zeros);
		}
		//free(getl->line);
	}
	fclose(shell->debug_file);
	return (0);
}




