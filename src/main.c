/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2020/12/26 12:54:50 by fmehdaou         ###   ########.fr       */
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
// 			return (i + 1);
// 		i++;
// 	}
// 	return (-1);
// }


void	errrors(char *err)
{
	ft_putendl_fd(err, 1);
}


// int	check_syntax(t_getl *getl,int i, char c)
// {
	

// 	int res;

// 	res = 0;
// 	getl->space = ' ';

// 	while(getl->line[++i])
// 	{ 
// 		if (c == '>')
// 			i++;
// 		else if (getl->line[i] == c)
// 			return (1); 
// 		while(getl->line[i] && getl->line[i] != c)
// 		{
// 			printf("|%c|\n",getl->line[i]);
// 			if (getl->line[i] != ' ')
// 				return (0);	
// 			i++;
// 		}
// 		res = (getl->space == ' ') ? 1 : 0;
// 	}
// 	return (res); // no err found
// }





// int	foreach_cmd(char *sp, t_getl *getl)
// {
	
// 	int err;
// 	int i;
// 	int aff;
	
// 	i = -1; 
// 	err = -1;
// 	printf("|%s|\n",sp);
// 	while(sp[++i])
// 	{
// 		if (sp[i] ==  '>' || sp[i] == '|')
// 		{
// 			err = (sp[i] == '>') ? INFILE : PIPE;
// 			if ((aff = check_syntax(getl, i, sp[i])))
// 			{
// 				printf("aff:%d\n",aff);
// 				return(err);
// 			}
// 			printf("aff:%d\n",aff);
				

// 		}
// 	}
	
	



// 	//TODO
// 	return (err);// -1 : everything is good

	
	

// }




// int	get_cmd(t_getl *getl)
// {
// 	int i;


// 	i = -1;
// 	getl->err = -1;
// 	getl->sp = ft_split(getl->line, ';');
// 	while(getl->sp[++i])
// 	{
// 		if ((getl->err = foreach_cmd(getl->sp[i], getl)) != -1)
// 		{
// 			errrors(g_mishell_err[getl->err]);
// 			break;
// 		}
// 	}
// 	return (getl->err);
// }




// int	check_comma(t_getl *getl, int *i, char c)
// {
// 	while(getl->line[++(*i)])
// 	{
// 		if (getl->line[*i] == ';' || getl->line[*i] == '|' || getl->line[*i] == '>' || getl->line[*i] == ' ')
// 			getl->line[*i] = -getl->line[*i]; //     1 ;
// 		else if (getl->line[*i] == c)
// 		{
// 			getl->quote = 0;
// 			return (*i);
// 		}
// 	}
// 	return (-1);
// }




// void	tozeros(char *s, int len)
// {
// 	s[len] = '\0';
// 	while(--len > -1)
// 		*s++ =  '0';
// } 



// int	toclear(t_getl *getl)
// {
// 	int i;

// 	getl->quote = 0;
// 	i = -1;
// 	while(getl->line[++i])
// 	{
// 		if (getl->line[i] == ';')
// 			if (check_syntax(getl, i, ';'))
// 				return(COMMA);
// 		if (getl->line[i] == (char)34 || getl->line[i] == (char)39)
// 		{
// 			getl->c = (getl->line[i] == (char)34) ? (char)34 : (char)39;
// 			getl->quote = 1;
// 			i = check_comma(getl, &i, getl->c);
// 		}
// 		if (getl->quote == 1)
// 			return (QUOTED);// failed		
// 	}
// 	return (-1); // nothing happed
// }

	void	init_state(t_getl *getl)
	{
		getl->s_quote = 0;
		getl->d_quote = 0;
		getl->dollar = 0;
		getl->semicolon = 0;
		getl->red_in = 0;
		getl->red_out = 0;
		getl->append = 0;
		getl->pipe = 0;
		getl->brake = 0;
	

	}



	int is_special_char(char c)
	{
		return (c == ';' || c == '|' || c == ' ');
	}



	int is_all_off(t_getl *getl)
	{
		return (getl->pipe || getl->semicolon ||  getl->red_in || getl->red_out);
	}



	int is_on(t_getl *getl)
	{
		int is_on;

		is_on = 0;
		if (getl->semicolon)
			is_on = 1;
		else if (getl->pipe)
			is_on = 2;
		else if (getl->red_in)
			is_on = 3;
		else if (getl->red_out)
			is_on = 4;
	



		return (is_on);// 0
	}


	void	verify_rest(t_getl *getl, int *i)
	{
		//TODO check the on and make it off 
		//printf("%d|%c|\n",getl->semicolon,getl->line[*i]);
		if (getl->semicolon && !is_special_char(getl->line[*i]) && getl->line[*i] != ' ')
			getl->semicolon = 0;
		else if (getl->pipe && !is_special_char(getl->line[*i]))
			getl->pipe = 0;
		else if (getl->red_in && !is_special_char(getl->line[*i]))
		{
			printf("> is off");
			getl->red_in = 0;
		}
		else if (getl->red_out && !is_special_char(getl->line[*i]))
		{
			printf(">> is off");
			getl->red_out = 0;
		}
		else
		{
			printf("%c\n",getl->line[*i]);
		}
		
			
		
		

			
		//printf("%d|%c|\n",getl->semicolon,getl->line[*i]);
		

	}


	int	verify_s_quote(t_getl *getl)
	{
		getl->s_quote = !(getl->s_quote);
		return (getl->s_quote);
	}

	int	verify_d_quote(t_getl *getl)
	{
		getl->d_quote = (getl->d_quote) ? 0 : 1;
		return (getl->d_quote);
	}

	int	verify_s_semicolon(t_getl *getl, int *i)
	{
		if (getl->s_quote || getl->d_quote)
			getl->line[*i] = -getl->line[*i];
		else if (is_all_off(getl) || !getl->i)
		{
			if (getl->line[*i - 1] == ';' || (getl->line[*i + 1] && getl->line[*i + 1] == ';'))
				errrors(g_mishell_err[COMMAD]);
			else 
				errrors(g_mishell_err[COMMA]);
			return (1);
		}
		else 
			getl->semicolon = 1;	
		return (0); // everything ok 
	}
	

	void	verify_space(t_getl *getl, int *i)
	{
		if (getl->s_quote || getl->d_quote)
			getl->line[*i] = -getl->line[*i];
	}


	
	

	int	verify_s_pipe(t_getl *getl, int *i)
	{
		printf("\n\n%d\n\n",is_all_off(getl));
		if (getl->s_quote || getl->d_quote)
			getl->line[*i] = -getl->line[*i];
		else if (is_all_off(getl) || !getl->i)
		{
			errrors(g_mishell_err[PIPE]);
			return (1);	
		}
		else 
			getl->pipe = 1;
		return (0);
	}




	int	verify_s_red(t_getl *getl, int *i)
	{
		
		if (getl->s_quote || getl->d_quote)
			getl->line[*i] =  -getl->line[*i];
		else if (getl->line[*i + 1] && getl->line[*i + 1] == '>')
		{
			printf(">> is on\n");
			getl->red_out = 1;
			getl->i += 2;
			
		}
		else if (is_all_off(getl))
		{
			errrors("error\n");
			return (1);	
		}
		else
		{
			printf("red is on\n");
			getl->red_in = 1;
		}	
		return (0);
	}
	
	
	int	verify_final(t_getl *getl)
	{
		int err;

		if (getl->s_quote || getl->d_quote)
		{
			err = (getl->s_quote) ? QUOTES : QUOTED;
			errrors(g_mishell_err[err]);
			return (1);
		}
		else if ((err = is_on(getl)) > 1)
		{
			if (err == 2)
				errrors(g_mishell_err[PIPE]);
			else if (err == 3 || err == 4)
				errrors(g_mishell_err[RED]);
			return (1);
		}
			
		return (0);
	}



int     main(int argc, char **argv, char **env)
{
	t_shell *shell;
	t_getl *getl;


	//t_lst list;

	shell = (t_shell*)malloc(sizeof(t_shell));
	getl = (t_getl*)malloc(sizeof(t_getl));
	

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



	// while (1)
	// {
	// 	ft_putstr_fd("\033[92mminishell$> \033[39m", 1);
	// 	if (get_next_line(0, &getl->line_t) > 0)
	// 	{
	// 		getl->line = ft_strtrim(getl->line_t, " "); // to check the enf if it conteins > |  >> 
	// 		getl->len = ft_strlen(getl->line);
	// 		if ((getl->err = toclear(getl)) != -1)
	// 		{
	// 			errrors(g_mishell_err[getl->err]);
	// 			continue;
	// 		}
	// 		if (get_cmd(getl) != -1)
	// 			continue;
	// 	}
	// 	//free(getl->line);
	// }













	while (1)
	{

		ft_putstr_fd("\033[92mminishell$> \033[39m", 1);
		if (get_next_line(0, &getl->line) > 0)
		{
			init_state(getl);
			getl->i = -1;
			while(getl->line[++(getl->i)])
			{
				if (getl->line[getl->i] == (char)39)
					verify_s_quote(getl);
				else if (getl->line[getl->i] == (char)34)
					verify_d_quote(getl);
				else if (getl->line[getl->i] == ' ')
					verify_space(getl, &getl->i);
				else if (getl->line[getl->i] == ';')
				{
					if (verify_s_semicolon(getl, &getl->i))
					{
						getl->brake = 1;
						break;
					}
						
				}
				// if (getl->line[getl->i] == '$')
				// 	verify_s_red_out(getl);
				else if (getl->line[getl->i] == '|')
				{
					if (verify_s_pipe(getl, &getl->i))
					{
						getl->brake = 1;
						break;
					}	
				}
				else if (getl->line[getl->i] == '>')
				{
					if (verify_s_red(getl, &getl->i))
					{
						printf("not here");
						getl->brake = 1;
						break;
					}	
				}
				// if (getl->line[getl->i] == '<')
				// 	verify_s_red_out(getl);
				else
				{
					// int j = getl->i;
					// while(getl->line[j++])
					// 	printf("%c",getl->line[j]);
					// printf("\n");
					printf("rest: %c\n",getl->line[getl->i]);
					verify_rest(getl, &getl->i);
				}
					

				
				
				

					
				
			}
			if (!getl->brake && verify_final(getl))
				continue;
			// printf("line:%s\n",getl->line);
		}
		free(getl->line);
	}
	fclose(shell->debug_file);
	return (0);
}




/*t_cmd *cmd;

	char *s;
	int i;
	
	//char *args;
	//int in;
	
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	int k = -1;
	while(sp[++k])
	{
		if (sp[k] < 0)
			sp[k] = -sp[k];

	}
	printf("fixed: |%s|\n", sp);


	getl->fd = 0;
	// getl->spp = ft_split(sp, '|');
	// while(getl->spp[++k])
	// 	printf("|%s|\n",getl->spp[k]);
	
	//getl-spp = ft_split(sp, '|');
*	s = ft_strtrim(sp, " ");
//	printf("|%s|\n",s);
	//cmd->c = ft_substr(s, 0, (i = indexof_char(s, " ")));
	//printf("\n\n|%s|\n", cmd->c);
	// //printf("\n\nin:%d \n\n",in);
	// in = skip_char(sp, " ", in);
	// //printf("\n\n\n\nin:%d endofargs:%lu\n\n\n\n",in, ft_strlen(sp) - in);
	// args = ft_substr(sp, in, ft_strlen(sp) - in);
	//printf("|cmd->c:|%s|\n|args:|%s|\n\n",cmd->c, arg*/