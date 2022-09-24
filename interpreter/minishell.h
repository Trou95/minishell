#ifndef _MINISHELL_H_
#define _MINISHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./Libft/libft.h"

#include <readline/readline.h>
#include <readline/history.h>


char **g_env;


char* ft_check_quote(const char *str);
char* ft_double_quote(const char *str,int *end_index);
char* ft_quote(const char *str,int *end_index);
char* ft_format(const char *str, int* env_len);

char* ft_envjoin(char* dst, char* src);
int ft_get_env(const char *str);
int ft_is_valid_env(const char *str);


#endif