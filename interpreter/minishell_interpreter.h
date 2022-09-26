#ifndef _MINISHELL_INTERPRETER_H_
#define _MINISHELL_INTERPRETER_H_

#include <stdio.h>
#include "../libft/libft.h"

char **g_env;

char **interpreter_array_format(char **arr);

char* ft_check_quote(const char *str);
char* ft_double_quote(const char *str,int *end_index);
char* ft_quote(const char *str,int *end_index);
char* ft_format(const char *str, int* env_len);

char* ft_envjoin(char* dst, char* src);
int ft_get_env_len(const char *str);
int ft_get_env(const char *str);
int ft_is_valid_env(const char *str);

void	ft_env_copy(char **env);


#endif