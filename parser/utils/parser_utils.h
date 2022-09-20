#ifndef _PARSER_UTILS_H_
#define _PARSER_UTILS_H_


#include "../minishell.h"

#include "strutils/parser_strutils.h"



char **parser_array_trim(char **str);
int	parser_array_cmp(char *str, char **arr);
int parser_array_getsize(char **arr);

int		parser_word_cnt(char *str, char **arr);
int	parse_non_redir_word_count(char **str, char **arr);
char	**parser_cmd_split(char* str, char c);
char **parser_redirect_split(char **str, char ***ret, char **arr);

int parser_quote_endidx(const char *str, char c);
int parser_check_quetes(char *str);
int parser_check_doublequote(char *str, int *double_quote, int *qoute);
int parser_check_quote(char *str, int *quote);

char *ft_free(char *ptr);
char **ft_double_free(char **ptr, size_t size);

int parser_check_valid_syntax(char **str, char **arr);

int	err_prnt(char *err_desc, char *err_code);
void	*ft_space_cntrl(const char *s, char c);




#endif