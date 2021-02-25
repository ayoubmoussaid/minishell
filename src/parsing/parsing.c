/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:21 by amoussai          #+#    #+#             */
/*   Updated: 2021/02/25 14:55:30 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
void verify_rest(t_getl *getl, int *i)
{
	//TODO check the on and make it off
	if (getl->semicolon && !is_special_char(getl->line[*i]) && getl->line[*i] != ' ')
		getl->semicolon = 0;
	else if (getl->pipe && !is_special_char(getl->line[*i]))
		getl->pipe = 0;
	else if (getl->red_in && !is_special_char(getl->line[*i]))
		getl->red_in = 0;
	else if (getl->append && !is_special_char(getl->line[*i]))
		getl->append = 0;
	else if (getl->red_out && !is_special_char(getl->line[*i]))
		getl->red_out = 0;
}

int verify_s_quote(t_getl *getl)
{
	if (getl->d_quote)
		return (getl->s_quote);
	getl->s_quote = !(getl->s_quote);
	return (getl->s_quote);
}

int verify_d_quote(t_getl *getl)
{
	if (getl->s_quote == 1 || (getl->d_quote && getl->line[getl->i - 1] == '\\'))
		return (getl->d_quote);
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

int verify_s_semicolon(t_getl *getl, int *i)
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

void verify_space(t_getl *getl, int *i)
{
	if (getl->s_quote || getl->d_quote)
		getl->line[*i] = -getl->line[*i];
}

int verify_s_pipe(t_getl *getl, int *i)
{
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

int verify_s_red(t_getl *getl, int *i)
{

	if (getl->s_quote || getl->d_quote)
		getl->line[*i] = -getl->line[*i];
	else if (getl->line[*i + 1] && getl->line[*i + 1] == '>')
	{
		if (getl->red_in || getl->red_out || getl->append)
		{
			errrors(g_mishell_err[INFILED]);
			return 1;
		}
		getl->append = 1;
		getl->i += 1;
	}
	else
	{
		if (getl->red_in || getl->red_out || getl->append)
		{
			errrors(g_mishell_err[INFILE]);
			return 1;
		}
		getl->red_in = 1;
	}
	getl->semicolon = 0;
	getl->pipe = 0;
	return (0);
}

int verify_s_red_out(t_getl *getl, int *i)
{
	if (getl->s_quote || getl->d_quote)
		getl->line[*i] = -getl->line[*i];
	else
	{
		if (getl->red_in || getl->red_out || getl->append)
		{
			errrors(g_mishell_err[OUTFILE]);
			return 1;
		}
		getl->red_out = 1;
		getl->semicolon = 0;
		getl->pipe = 0;
	}
	return (0);
}

int verify_final(t_getl *getl)
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

void parse_line(t_getl *getl)
{
	int ret;
	while (1)
	{
		g_shell->exit_status == 0 ? ft_putstr_fd("\033[92mminishell$> \033[39m", STDOUT_FILENO) : ft_putstr_fd("\033[91mminishell$> \033[39m", STDOUT_FILENO);
		//getl->line = ft_strdup("sleep 3 | echo");	
		if ((ret = get_next_line(0, &getl->line)) == -1)
			error_handle(E_STANDARD, errno, "");
		else if (ft_strlen(getl->line) == 0 && ret == 0)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		else
		{
			init_state(getl);
			getl->i = -1;
			while (getl->line[++(getl->i)] && !getl->brake)
			{
				if (getl->line[getl->i] == (char)39)
					verify_s_quote(getl);
				else if (getl->line[getl->i] == (char)34)
					verify_d_quote(getl);
				else if (getl->line[getl->i] == ' ')
					verify_space(getl, &getl->i);
				else if (getl->line[getl->i] == ';' || getl->line[getl->i] == '|' || getl->line[getl->i] == '>' || getl->line[getl->i] == '<')
				{
					if (((getl->line[getl->i] == ';' && verify_s_semicolon(getl, &getl->i)) || (getl->line[getl->i] == '|' && verify_s_pipe(getl, &getl->i)) || (getl->line[getl->i] == '>' && verify_s_red(getl, &getl->i)) || (getl->line[getl->i] == '<' && verify_s_red_out(getl, &getl->i))))
						getl->brake = 1;
				}
				else
					verify_rest(getl, &getl->i);
			}
			if (!getl->brake && verify_final(getl))
				continue;
			else if (getl->brake == 1)
				continue;
			else
				get_command(getl);
		}
		free(getl->line);
	}
}
