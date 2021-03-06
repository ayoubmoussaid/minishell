/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:29:45 by amoussai          #+#    #+#             */
/*   Updated: 2021/03/06 17:42:33 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*co_str(char *str1, char *str2, char *str3)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strjoin(str1, str2);
	tmp2 = ft_strjoin(tmp, str3);
	free(tmp);
	return (tmp2);
}

void	pr_er(char *str)
{
	ft_putendl_fd(str, 2);
	free(str);
}

int		error_handle(int e, int exit_code, char *n)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!n)
		n = "";
	(e == E_CNF) ? pr_er(ft_strjoin(n, ": command not found")) : 1;
	(e == E_WPATH) ? pr_er(ft_strjoin(n, ": No such file or directory")) : 1;
	(e == E_ISDIR) ? pr_er(ft_strjoin(n, ": is a directory")) : 1;
	(e == E_STANDARD) ? pr_er(co_str(n, ": ", strerror(errno))) : 1;
	(e == E_TMA) ? pr_er(ft_strjoin(n, ": too many arguments")) : 1;
	(e == E_CD_NOFOD) ? pr_er(co_str("cd: ", n, ": No such file or directory"))
		: 1;
	(e == E_CD_HOME) ? pr_er(ft_strdup("cd: HOME not set")) : 1;
	(e == E_EXPORT_NOTVAID) ? pr_er(
		co_str("export: `", n, "': not a valid identifier")) : 1;
	(e == E_EXIT_ARG) ? pr_er(
		co_str("exit: ", n, ": numeric argument required")) : 1;
	(e == E_UNSET_NOTVAID) ? pr_er(
		co_str("unset: `", n, "': not a valid identifier")) : 1;
	(e == E_SYNTAX) ? ft_putendl_fd(n, 2) : 1;
	g_shell->exit_status = exit_code;
	return (exit_code);
}
