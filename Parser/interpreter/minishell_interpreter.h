#ifndef _MINISHELL_INTERPRETER_H_
#define _MINISHELL_INTERPRETER_H_

#include <stdio.h>
#include "../parser/utils/parser_utils.h"
#include "../../Libft/libft.h"


char **interpreter_array_format(char **arr, char **env);

char* ft_check_quote(const char *str, char **env);
char* ft_double_quote(const char *str,int *end_index, char **env);
char* ft_quote(const char *str,int *end_index);
char* ft_format(const char *str, int* env_len, char	**env);
char* interpreter_qouete(const char *str, char qouete, int *index, char **env);

char* ft_envjoin(char* dst, char* src);
int ft_get_env_len(const char *str);
int ft_get_env(const char *str, char **env);
int ft_is_valid_env(const char *str);


#endif