
#include "../headers/minishell.h"

int get_index_of_separator(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
			break;
		i++;
	}
	return (i);
}

void override_str(char **str, int index)
{
	while ((*str)[index] != '\0')
	{
		(*str)[index] = (*str)[index + 1];
		index++;
	}
}

int check_for_simple_double(char **line, int *i, int *s, int *d)
{
	int x = 0;

	if ((*line)[*i] == '\"' && *s == 0)
	{
		override_str(line, *i);
		*d = !(*d);
		x = 1;
	}
	if ((*line)[*i] == '\'' && *d == 0)
	{
		override_str(line, *i);
		(*s) = !(*s);
		if (*s == 0)
			(*i)--;
		x = 1;
	}
	return (x);
}

int check_for_after_backslash(char c)
{
	return (c == '$' || c == '\"' || c == '\\');
}

void flip_line(char **line)
{
	int i = -1;
	int d = 0;
	int s = 0;
	//TODO variable expansion and backslash handle in double quotes
	while ((*line)[++i] != '\0')
	{
		while (check_for_simple_double(line, &i, &s, &d));
		if ((*line)[i] == '$' && s == 0)
		{
			char *tmp1;
			char *tmp2;
			int index = 1;
			if ((*line)[i + 1] == '?')
				tmp2 = ft_itoa(g_shell->exit_status);
			else
			{
				index = get_index_of_separator((*line) + i + 1);
				tmp1 = ft_substr((*line) + i + 1, 0, index);
				tmp2 = get_env_var(tmp1);
				tmp2 = tmp2 ? tmp2 : ft_strdup("");
				free(tmp1);
			}
			if (index != 0 || (index == 0 && d == 0 && s == 0 && ((*line)[i + 1] == '\'' || (*line)[i + 1] == '\"')))
			{
				tmp1 = ft_strjoin(tmp2, (*line) + i + index + 1);
				free(tmp2);
				(*line)[i] = '\0';
				tmp2 = ft_strjoin((*line), tmp1);
				free(tmp1);
				free((*line));
				(*line) = tmp2;
				if((*line)[i] == '\"' || (*line)[i] == '\'')
					i--;
			}
		}
		if (d == 1 && (*line)[i] == '\\' && check_for_after_backslash((*line)[i + 1]))
			override_str(line, i);
		if ((d || s) && (*line)[i] > 0)
			(*line)[i] = -(*line)[i];
	}
	if (d || s)
		ft_putendl_fd("Syntax error", STDERR_FILENO);
}
