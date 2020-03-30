

#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>

#include "./gnl/get_next_line.h"
#include "./libft/libft.h"


typedef struct  s_commands{
	char	*line;
	char	**command;
	char	**flags;
	char	*file;
}				t_commands;

#endif