#ifndef _PARSER_UTILS_H_
#define _PARSER_UTILS_H_


#include "../minishell_types.h"
#include "../libft/libft.h"

char **parser_array_trim(char **str);
int	parser_array_cmp(char *str, char **arr);
int parser_array_getsize(char **arr);

int		parser_word_cnt(char *str, char **arr);
int	parse_non_redir_word_count(char **str, char **arr);
char	**parser_cmd_split(char* str, char c);
t_data *parser_redirect_split(char *str, char **arr);
t_data *parser_redirect_add(char *command, char *redir, char *redir_arg);
char *parser_redirect_cmdjoin(char *n_cmd, char* cmd);
int parser_redirect_check(char *str, char **arr);
int parser_redirect_add_cmdarg(t_redir_var *v, char *str, char **arr);
char *parser_redirect_cmdjoin(char *n_cmd, char* cmd);
int parser_redirect_init_vars(char *str, t_redir_var *v);
t_data *parser_redirect_add(char *command, char *redir, char *redir_arg);




int parser_quote_endidx(const char *str, char c);
int parser_check_quetes(char *str);
int parser_check_doublequote(char *str, int *double_quote, int *qoute);
int parser_check_quote(char *str, int *quote);

char *ft_free(char *ptr);
char **ft_double_free(char **ptr, size_t size);

int parser_check_valid_syntax(char **str, char **arr);

int	err_prnt(char *err_desc, char *err_code);
void	*ft_space_cntrl(const char *s, char c);

char **parser_process(char *str);


void	array_cleaner(char **arr);
void	array_writer(char **arr);

//strutils
char *ft_free_strjoin(char *dst, const char *src);
int ft_get_chrindex(const char* str, char c);
char *ft_str_clearspace(const char *str);
int ft_str_clearspace_end(const char *str);

size_t ft_wordlen(char *str, char **arr);
char *ft_get_next_word(char *str, char **arr);

int ft_error(char *err_msg, char *err_arg, int err_type);




#endif