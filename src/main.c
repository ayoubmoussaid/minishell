/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/10 14:59:35 by fmehdaou         ###   ########.fr       */
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



// void	printsp(char **sp)
// {
// 	int i = -1;

// 	printf("--------start--------\n");
// 	while(sp[++i])
// 		printf("|%s|\n",sp[i]);
// 	printf("---------end---------\n");
// }


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


// int indexof_char(char *str, char *c)
// {
// 	int i;
// 	char *s;

// 	i = -1;
// 	s = ft_strtrim(str, c);
// 	while(s[++i])
// 	{
// 		if (s[i] == c[0])
// 			return (i);
// 	}
// 	return (-1);
// }

// int skip_char(char *s, char *c, int start)
// {
// 	int i;

// 	i = start;
// 	while(s[i])
// 	{
// 		if (s[i] == c[0] && s[i + 1] != c[0])
// 			return (i+1);
// 		i++;
// 	}
// 	return (-1);
// }








// void	foreach_cmd(char *sp)
// {
	
// 	t_cmd *cmd;
// 	char *args;
// 	int in;
	

// 	// int   in;

// 	// in = indexof_char(sp, " ");
// 	cmd = (t_cmd*)malloc(sizeof(t_cmd));
// 	cmd->c = ft_substr(sp, 0, (in = indexof_char(sp, " ")));
// 	in = skip_char(sp, " ", in);
// 	args = ft_substr(sp, in, ft_strlen(sp) - in);
// 	printf("|cmd->c:|%s|\n|args:|%s|\n\n",cmd->c, args);
	


	
	

	
// }




// void	get_cmd(t_getl *getl)
// {
// 	int i;

// 	i = -1;
// 	getl->sp = ft_split(getl->line_t, ';');
// 	while(getl->sp[++i])
// 	{
// 		foreach_cmd(getl->sp[i]);
// 		free(getl->sps);
// 	}
	
	
// }


void	errrors(char *err)
{
	ft_putendl_fd(err, 1);
}



int	check_comma(t_getl *getl, int *i)
{
	while(getl->line_t[++(*i)])
	{
		if (getl->line_t[*i] == ';')
		{
			getl->zeros[*i] = '1'; //;
			getl->line_t[*i] = '1'; //;
		}
		else if (getl->line_t[*i] == '"')
		{
			getl->quote = 0;
			return (*i);
		}
	}
	return (-1);
}




void	tozeros(char *s, int len)
{
	while(len--)
		*s++ =  '0';
} 

int	toclear(t_getl *getl)
{
	int i;

	getl->quote = 0;
	i = -1;
	while(getl->line_t[++i])
	{
		if (getl->line_t[i] == '"')
		{
			getl->quote = 1;
			i = check_comma(getl, &i);
		}
		if (getl->quote == 1)
		{
			//printf("error\n");
			return (-1);// failed
		}

		// else if (getl->line_t[i] == (char)39)
		// {
		// 	printf("syntax error\n");
		// }
				
	}
	return (1);
}






int     main(int argc, char **argv, char **env)
{
	t_shell *shell;
	t_getl *getl;
	int len;

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
		if (get_next_line(0, &getl->line) > 0)
		{
			
			// getl->line_t =  ft_strtrim(getl->line, " ");
			// len = ft_strlen(getl->line_t);

			// get_cmd(getl);
			getl->line_t =  ft_strtrim(getl->line, " ");
			printf("|%s|\n",getl->line_t);
			len = ft_strlen(getl->line_t);
			getl->zeros = (char*)malloc(sizeof(char) * (len + 1));
			tozeros(getl->zeros, len);
			printf("|%s|\n\n\n\n",getl->zeros);
			if ((getl->err = toclear(getl)) == -1)
			{
				errrors(g_mishell_err[QUOTES]);
				continue;// show err and continue to the next cmd
			}
				
			printf("|%s|\n",getl->zeros);
			printf("|%s|\n",getl->line_t);

			
				
			
			//printsp(getl);

		}
			


		free(getl->line);
	}
	//fprintf(shell->debug_file, "hello %d\n", 22);


	
	
	
	
	/* pid_t pid = fork();
	if(pid == 0)
	{
		char *args[] = {"/bin/ls", (char *)0};
		char *env_args[] = {(char*)0};
		printf("salut from child\n");
		int x = execve(args[0], args, env_args);
		printf("child says: %d\n", x);
		sleep(2);
		exit(0);
	}
	else if (pid > 0)
	{
		int status;
		printf("parent process here\n");
		waitpid(pid, &status, 0);
		printf("child process exited %d | %d\n", pid, getpid());	
	}
	else
	{
		printf("some error occured!\n");
	} */

	//pause();
	fclose(shell->debug_file);
	return (0);
}






/* int     ft_len(char **tab){
	int i;

	i=0;
	while(tab[i] != NULL){
		i++;
	}
	return i;
}

int ft_verify(char *str){
	int i;

	i = 0;
	while (str[i] != '\0'){
		if (str[i] == ';' && str[i + 1] == ';'){
			return (0);
		}
	}
	return (1);
}

void    parse_line(char *str){
	
	char **str_table = ft_split(str, ';');
	printf("\nlen: %d\n", ft_len(str_table));
	int i = 0;
	while(str_table[i] != NULL){
		printf("-- %s --\n", str_table[i]);
		i++;
	}
}

void    read_line(){
	char    *line;
	int     ret = 0;
	ft_putstr_fd("\x1B[92m->minishell=> \x1B[39m", STDOUT_FILENO);
	while((ret = get_next_line(STDIN_FILENO, &line)) != -1){
		ft_putstr_fd(line, STDOUT_FILENO);
		parse_line(line);
		free(line);
		ft_putstr_fd("\x1B[92m\n-> minishell=> \x1B[39m", STDOUT_FILENO);
	}
} */
