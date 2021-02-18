#include "../headers/minishell.h"


int		check_for_slash(char *str)
{
	int i;

	i = -1;
	while (str && str[++i] != '\0')
		if (str[i] == '/')
			return (1);
	return (0);	
}

int		check_builtins(char *str)
{
	int i;

	i = -1;
	while(g_builtins[++i])
		if(ft_strcmp(g_builtins[i], str) == 0)
			return (i);
	return (-1);
}

char	*get_path(t_cmd	*cmd)
{
	char			*path;
	char			**all_paths;
	int				i;
	DIR				*dfd;
	struct dirent	*dp;
	struct stat		stbuf;

	i = -1;
	path = get_env_var("PATH");
	all_paths = ft_split(path, ':');
	while (all_paths[++i] != 0)
	{
		if ((dfd = opendir(all_paths[i])) == NULL)
			continue;
		while ((dp = readdir(dfd)) != NULL)
		{
			path = ft_specialjoin(all_paths[i], dp->d_name, '/');
			if (stat(path, &stbuf) == -1)
				continue;
			if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
				continue;
			if(ft_strcmp(dp->d_name, cmd->c) == 0)
				return (path);
		}
		closedir(dfd);
	}
	return NULL;
}

int 	get_real_cmd(t_cmd *cmd)
{
	int		index;

	index = -1;
	
	if(check_for_slash(cmd->c) || (index = check_builtins(cmd->c)) != -1)
		cmd->executable = cmd->c;
	else
		cmd->executable = get_path(cmd);
	if(cmd->executable == NULL)
		index = -2;
	return (index);
}
