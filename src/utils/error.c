
#include "../headers/minishell.h";

# define E_CNF 0; //command not found
# define E_STANDARD 1; //standard errors that include command name + error in errno
# define E_FILE 2; // errors related to opening files
# define E_TMA 4; //too many arguments
# define E_CD_NOFOD 5; //NO such file or directory for cd
# define E_CD_HOME 6; //HOME not set
# define E_EXPORT_NOTVAID 7; // export not valid iderntifier
# define E_UNSET_NOTVAID 8;// unset not valid identifier

char concat_strings(char *str1, char *str2, char *str3)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strjoin(str1, str2);
	tmp2 = ft_strjoin(tmp, str3);
	free(tmp);
	return (tmp2);
}

void	error(int err, int exit_code, char	*need)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	
}
