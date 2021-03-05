/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/05 16:18:17 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
void verify_rest(t_getl *g_getl, int *i)
{
	//TODO check the on and make it off
	if (g_getl->semicolon && !is_special_char(g_getl->line[*i]) && g_getl->line[*i] != ' ')
		g_getl->semicolon = 0;
	else if (g_getl->pipe && !is_special_char(g_getl->line[*i]))
		g_getl->pipe = 0;
	else if (g_getl->red_in && !is_special_char(g_getl->line[*i]))
		g_getl->red_in = 0;
	else if (g_getl->append && !is_special_char(g_getl->line[*i]))
		g_getl->append = 0;
	else if (g_getl->red_out && !is_special_char(g_getl->line[*i]))
		g_getl->red_out = 0;
}


int	quote_handler(t_getl *g_getl, char c)
{
	if(g_getl->line[g_getl->i] == c && g_getl->line[g_getl->i + 1] == c )
	{
		if ((g_getl->i == 0 || (g_getl->line[g_getl->i - 1] && g_getl->line[g_getl->i - 1] == ' ')) &&
		 ((g_getl->line[g_getl->i + 2] && g_getl->line[g_getl->i + 2] == ' ') || g_getl->line[g_getl->i + 2] == '\0' ))
		{
			g_getl->line[g_getl->i] = -g_getl->line[g_getl->i];
			g_getl->line[g_getl->i + 1] = -g_getl->line[g_getl->i + 1];
			return (1);
		}
	}
	return (0);
}



void verify_s_quote(t_getl *g_getl)
{
	if (quote_handler(g_getl, '\'') || g_getl->d_quote)
		return ;
	g_getl->s_quote = !(g_getl->s_quote);
}

int verify_d_quote(t_getl *g_getl)
{
	if(quote_handler(g_getl, '\"'))
		return (g_getl->d_quote);
	if (g_getl->s_quote == 1 || (g_getl->d_quote && g_getl->line[g_getl->i - 1] == '\\'))
		return (g_getl->d_quote);
	else if (!g_getl->d_quote)
	{
		g_getl->semicolon = 0;
		g_getl->pipe = 0;
		g_getl->red_in = 0;
		g_getl->append = 0;
		g_getl->d_quote = 1;
	}
	else
		g_getl->d_quote = 0;
	return (g_getl->d_quote);
}

int verify_s_semicolon(t_getl *g_getl, int *i)
{

	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
	else if (is_all_off(g_getl) || !g_getl->i)
	{
		if (g_getl->line[*i - 1] == ';' || (g_getl->line[*i + 1] && g_getl->line[*i + 1] == ';'))
			errrors(g_mishell_err[COMMAD]);
		else
			errrors(g_mishell_err[COMMA]);
		return (1);
	}
	else
		g_getl->semicolon = 1;
	return (0); // everything ok
}

void verify_space(t_getl *g_getl, int *i)
{
	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
}

int verify_s_pipe(t_getl *g_getl, int *i)
{
	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
	else if (is_all_off(g_getl) || !g_getl->i)
	{
		errrors(g_mishell_err[PIPE]);
		return (1);
	}
	else
		g_getl->pipe = 1;
	return (0);
}

int verify_s_red(t_getl *g_getl, int *i)
{

	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
	else if (g_getl->line[*i + 1] && g_getl->line[*i + 1] == '>')
	{
		if (g_getl->red_in || g_getl->red_out || g_getl->append)
		{
			errrors(g_mishell_err[INFILED]);
			return 1;
		}
		g_getl->append = 1;
		g_getl->i += 1;
	}
	else
	{
		if (g_getl->red_in || g_getl->red_out || g_getl->append)
		{
			errrors(g_mishell_err[INFILE]);
			return 1;
		}
		g_getl->red_in = 1;
	}
	g_getl->semicolon = 0;
	g_getl->pipe = 0;
	return (0);
}

int verify_s_red_out(t_getl *g_getl, int *i)
{
	if (g_getl->s_quote || g_getl->d_quote)
		g_getl->line[*i] = -g_getl->line[*i];
	else
	{
		if (g_getl->red_in || g_getl->red_out || g_getl->append)
		{
			errrors(g_mishell_err[OUTFILE]);
			return 1;
		}
		g_getl->red_out = 1;
		g_getl->semicolon = 0;
		g_getl->pipe = 0;
	}
	return (0);
}

int verify_final(t_getl *g_getl)
{
	int err;

	if (g_getl->s_quote || g_getl->d_quote)
	{
		err = (g_getl->s_quote) ? QUOTES : QUOTED;
		errrors(g_mishell_err[err]);
		return (1);
	}
	else if ((err = is_on(g_getl)) > 1)
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

void parse_line(t_getl *g_getl)
{
	int ret;
	while (1)
	{
		g_shell->exit_status == 0 ? ft_putstr_fd("\033[92mminishell$> \033[39m", STDOUT_FILENO) : ft_putstr_fd("\033[91mminishell$> \033[39m", STDOUT_FILENO);
		// g_getl->line = ft_strdup("echo $PWD; echo $OLDPWD; cd '' ''; pwd; echo $PWD; echo $OLDPWD");	
		if ((ret = get_next_line(0, &g_getl->line)) == -1)
			error_handle(E_STANDARD, errno, "");
		else if (ft_strlen(g_getl->line) == 0 && ret == 0)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		else
		{
			init_state(g_getl);
			g_getl->i = -1;
			while (g_getl->line[++(g_getl->i)] && !g_getl->brake)
			{
				if (g_getl->line[g_getl->i] == (char)39)
					verify_s_quote(g_getl);
				else if (g_getl->line[g_getl->i] == (char)34)
					verify_d_quote(g_getl);
				else if (g_getl->line[g_getl->i] == ' ')
					verify_space(g_getl, &g_getl->i);
				else if (g_getl->line[g_getl->i] == ';' || g_getl->line[g_getl->i] == '|' || g_getl->line[g_getl->i] == '>' || g_getl->line[g_getl->i] == '<')
				{
					if (((g_getl->line[g_getl->i] == ';' && verify_s_semicolon(g_getl, &g_getl->i)) || (g_getl->line[g_getl->i] == '|' && verify_s_pipe(g_getl, &g_getl->i)) || (g_getl->line[g_getl->i] == '>' && verify_s_red(g_getl, &g_getl->i)) || (g_getl->line[g_getl->i] == '<' && verify_s_red_out(g_getl, &g_getl->i))))
						g_getl->brake = 1;
				}
				else
					verify_rest(g_getl, &g_getl->i);
			}
			if (!g_getl->brake && verify_final(g_getl))
				continue;
			else if (g_getl->brake == 1)
				continue;
			else
				get_command(g_getl);
		}
		free(g_getl->line);
	}
}
