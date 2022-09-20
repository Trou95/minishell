#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "utils/parser_utils.h"
#include "libft/libft.h"

#ifndef NULL
# define NULL 0
#endif

typedef struct s_redir_var
{
	int idx;
	int n_idx;
	int k_idx;
	int last_idx;
	int arr_idx;
} t_redir_var;


char **parser_process(char *str);


void	array_cleaner(char **arr);
void	array_writer(char **arr);








#endif