/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/01 16:55:10 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void	errrors(char *err)
{
	ft_putendl_fd(err, 1);
}

int		check_for_slash(char *str)
{
	int i;

	i = -1;
	while (str && str[++i] != '\0')
		if (str[i] == '/')
			return (1);
	return (0);	
}


/*linekd list of cmd*/


/*syntax errors*/
	void	init_state(t_getl *getl)
	{
		getl->s_quote = 0;
		getl->d_quote = 0;
		getl->dollar = 0;
		getl->semicolon = 0;
		getl->red_in = 0;
		getl->append = 0;
		getl->append = 0;
		getl->pipe = 0;
		getl->brake = 0;
		getl->red_out = 0;

	}

	int is_special_char(char c)
	{
		return (c == ';' || c == '|' || c == ' ');
	}

	int is_all_off(t_getl *getl)
	{
		return (getl->pipe || getl->semicolon ||  getl->red_in || getl->append || getl->red_out);
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
		else if (getl->append)
			is_on = 4;
		else if (getl->red_out)
			is_on = 5;
	



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
			// printf("> is off");
			getl->red_in = 0;
		}
		else if (getl->append && !is_special_char(getl->line[*i]))
		{
			// printf(">> is off");
			getl->append = 0;
		}
		else if(getl->red_out && !is_special_char(getl->line[*i]))
		{
			getl->red_out = 0;
		}
		else
		{
			// printf("%c\n",getl->line[*i]);
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
		if (!getl->d_quote)
		{
			getl->semicolon = 0;
			getl->pipe = 0;
			getl->red_in = 0;
			getl->append = 0;
			getl->d_quote = 1;
		}
		else
			getl->d_quote = 0;
		return (getl->d_quote);
	}

	int	verify_s_semicolon(t_getl *getl, int *i)
	{
		
		if (getl->s_quote || getl->d_quote)
			getl->line[*i] = -getl->line[*i];
		else if (is_all_off(getl) || !getl->i)
		{
			// write(1, "hi\n", 3);
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
		// printf("\n\n%d\n\n",is_all_off(getl));
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
			if(getl->red_in || getl->red_out || getl->append)
			{
				errrors(g_mishell_err[INFILED]);
				return 1;
			}
			// printf(">> is on\n");
			getl->append = 1;
			getl->i += 1;
		}
		else
		{
			if(getl->red_in || getl->red_out || getl->append)
			{
				errrors(g_mishell_err[INFILE]);
				return 1;
			}
			// printf("red is on\n");

			getl->red_in = 1;
		}
		getl->semicolon = 0;
		getl->pipe = 0;
		return (0);
	}

	int verify_s_red_out(t_getl *getl, int *i)
	{
		if (getl->s_quote || getl->d_quote)
			getl->line[*i] =  -getl->line[*i];
		else
		{
			if(getl->red_in || getl->red_out || getl->append)
			{
				errrors(g_mishell_err[OUTFILE]);
				return 1;
			}
			getl->red_out = 1;
			getl->semicolon = 0;
			getl->pipe = 0;
		}
			
		return(0);

	}

	int	verify_final(t_getl *getl)
	{
		// write(1, "here\n", 5);
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
			// else if (err == 5 && err == 3)
			// 	errrors(g_mishell_err[INFILE]);
			// else if (err == 5 && err == 3)
			// 	errrors(g_mishell_err[INFILED]);
			else if (err == 3 || err == 4 || err == 5)
				errrors(g_mishell_err[RED]);
			return (1);
		}
		return (0);
	}

	/*getting cmds*/

	// void	filterd_line(t_getl *getl)
	// {
	// 	int i;

	// 	i = -1;
	// 	while(getl->line[++i])
	// 	{
	// 		if (getl->line[i] < 0)
	// 			getl->line[i] =  -getl->line[i];
	// 	}
	// }











	void	printsplit(char **sp)
	{
		int i = -1;

		// printf("--------start--------\n");
		while(sp[++i])
			printf("|%s|\n",sp[i]);
		// printf("---------end---------\n");
	}



	// t_cmd 	*add_new_cmd(t_cmd *cmd)
	// {
	// 	int i;

	// 	i = 0;

	// 	while(cmd->next)
	// 		i++;
	// 	cmd->c  =  
	// 	cmd->args = 
	// 	cmd->files = 
	// 	cmd->next =  NULL;
		

	// 	return (cmd);
	// }


	// t_pipeline *add_new_pipeline(t_pipeline *pipelines)
	// {

	// 	int i;
	// 	t_pipeline *prevpipe;


	// 	i = 0;
	// 	prevpipe = NULL;
	// 	while(pipelines->next)
	// 	{
	// 		prevpipe = pipelines->next;
	// 		i++;
	// 	}
	// 	// pipelines->pipe = add_new_cmd();
	// 	pipelines->next = prevpipe;
		



	// }



	void	ft_free(char **s)
	{
		int i;

		i = -1;
		while(s[++i])
		{
			free(s[i]);
			s[i] = NULL;
		}
		s = NULL;
	}

	int sp_len(char **str)
	{
		int i;

		i = 0;
		while(*str)
			i++;
		return(i);
	}



	// int	ft_pipelinelen(t_pipeline *t)
	// {
	// 	int len;

	// 	len = 1;
	// 	if (!t)
	// 		len = 0;
	// 	while(t->next)
	// 		len++;
	// 	return(len);
	// }



void	print_list(t_shell *shell)
{
	t_pipeline *current;

	current = shell->head;
	while(current)
	{
		printf("|%s|\n", current->pipe->c);
		current = current->next;
	}
	printf("end of list\n");
	
}


void clear_list(t_shell *shell)
{
	t_pipeline *current;
	t_pipeline *next_node;
	
	printf("here\n");
	current = shell->head;
	while(current)
	{
		next_node = current->next;
		free(current); // free inside before free current
		current =  NULL;
		current = next_node;
	}
	current = NULL;
}


// t_cmd	*get_cmd_list(t_shell *shell, char **pipes)
// {
// 	int i;

// 	i = 0;
// 	t_cmd *cmd;
// 	while(pipes[i])
// 	{
// 		cmd = (t_cmd*)malloc(sizeof(t_cmd));
// 		if ()






// 		i++;
// 	}





// }

void	add_new_pipe(t_shell *shell, t_getl *getl, int i)
{

	t_pipeline *pipeline;
	t_pipeline *current;

	int i;

	current = NULL;
	pipeline = NULL;
	i = 0;
	pipeline = (t_pipeline*)malloc(sizeof(t_pipeline));
	pipeline->pipe = (t_cmd*)malloc(sizeof(t_cmd));
	pipeline->next = NULL;
	getl->sp_p = ft_split(getl->sp_c[i], '|');
	if (shell->head == NULL)
	{
		while(getl->sp_p[i])
		{
			get_new_cmd();
			i++;
		}
		// pipeline->pipe->c = ft_strdup(getl->sp_c[i]);
		shell->head = pipeline;	
	}
	else
	{
	
		current = shell->head;
		while(current->next)
			current = current->next;
		// pipeline->pipe->c = ft_strdup(getl->sp_c[i]);
		current->next = pipeline;
	}
	ft_free(getl->sp_p);
	// int j = 0;
	// while(getl->sp_p[j])
	// {
	// 	printf("**---------------%s---------------**\n",getl->sp_p[j]);
	// 	j++;
	// }

	
}


void	get_command(t_getl *getl, t_shell *shell)
{
	int i;		

	i = -1;
	getl->sp_c = ft_split(getl->line, ';');
	while(getl->sp_c[++i])
		add_new_pipe(shell,getl,i);
	ft_free(getl->sp_c);	
	print_list(shell);	
}



void    parse_line(t_getl *getl, t_shell *shell)
{
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
						// printf("not here");
						getl->brake = 1;
						break;
					}	
				}
				else if (getl->line[getl->i] == '<')
				{
					if (verify_s_red_out(getl, &getl->i))
					{
						getl->brake = 1;
						break;
					}
				}
				else
				{
					
					// printf("rest: %c\n",getl->line[getl->i]);
					verify_rest(getl, &getl->i);
				}
			}
			// printf("|%s|\n", getl->line);
			if (!getl->brake && verify_final(getl))
				continue;
			else if (getl->brake == 1)
				continue;
			else 
			{
				// get_command(getl, pipelines);
				get_command(getl, shell);

				// printf("%s\n",shell->head->pipe->c);
				// print_list(shell);
			}
				
			
		}
        free(getl->line);
    }
}




int     main(int argc, char **argv, char **env)
{
	t_shell *shell;
    t_getl *getl;


	shell = (t_shell*)malloc(sizeof(t_shell));
	shell->envs = NULL;
	shell->debug_file = fopen("debug.txt", "w");
	if (argc > 1)
		argv = NULL;
	my_env(env);
	getl = (t_getl*)malloc(sizeof(t_getl));
	shell->head = NULL;
    parse_line(getl, shell);
    fclose(shell->debug_file);
	return (0);
}

