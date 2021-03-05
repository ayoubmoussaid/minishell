
#include "../headers/minishell.h"

char *concat_strings(char *str1, char *str2, char *str3)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strjoin(str1, str2);
	tmp2 = ft_strjoin(tmp, str3);
	free(tmp);
	return (tmp2);
}

int error_handle(int err, int exit_code, char *need)
{
	char *str;

	str = NULL;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!need)
		need = "";
	(err == E_CNF) ? ft_putendl_fd((str = ft_strjoin(need, ": command not found")), STDERR_FILENO) : NULL;
	(err == E_WPATH) ? ft_putendl_fd((str = ft_strjoin(need, ": No such file or directory")), STDERR_FILENO) : NULL;
	(err == E_ISDIR) ? ft_putendl_fd((str = ft_strjoin(need, ": is a directory")), STDERR_FILENO) : NULL;
	(err == E_STANDARD) ? ft_putendl_fd((str = concat_strings(need, ": ", strerror(errno))), STDERR_FILENO) : NULL;
	(err == E_TMA) ? ft_putendl_fd((str = ft_strjoin(need, ": too many arguments")), STDERR_FILENO) : NULL;
	(err == E_CD_NOFOD) ? ft_putendl_fd((str = concat_strings("cd: ", need, ": No such file or directory")), STDERR_FILENO) : NULL;
	(err == E_CD_HOME) ? ft_putendl_fd((str = ft_strdup("cd: HOME not set")), STDERR_FILENO) : NULL;
	(err == E_EXPORT_NOTVAID) ? ft_putendl_fd((str = concat_strings("export: `", need, "': not a valid identifier")), STDERR_FILENO) : NULL;
	(err == E_EXIT_ARG) ? ft_putendl_fd((str = concat_strings("exit: ", need, ": numeric argument required")), STDERR_FILENO) : NULL;
	(err == E_UNSET_NOTVAID) ? ft_putendl_fd((str = concat_strings("unset: `", need, "': not a valid identifier")), STDERR_FILENO) : NULL;
	(err == E_SYNTAX) ? ft_putendl_fd(need, STDERR_FILENO) : 1;
	g_shell->exit_status = exit_code;
	free(str);
	return (exit_code);
}
