#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "../../minishell_types.h"
# include "../../libft/libft.h"

char	**parser_process(char *str);

//Parser_split
char	**parser_cmd_split(char *str, char c);
//char **parser_redirect_split(char **str, char ***ret, char **arr);
//int		parser_word_cnt(char *str, char **arr);
//int	parse_non_redir_word_count(char **str, char **arr);

//Parser _redirect
int		parser_redirect_check(char *str, char **arr);
int		parser_redirect_init_vars(char *str, t_redir_var *v);
char	*parser_redirect_cmdjoin(char *n_cmd, char *cmd);
char	**parser_redirect(char **str);
t_data	*parser_redirect_split(char *str, char **arr);
t_data	*parser_redirect_add(char *command, char *redir, char *redir_arg);
int		parser_redirect_add_cmdarg(t_redir_var *v, char *str, char **arr);

//Parser_qoute
int		parser_quote_endidx(const char *str, char c);
int		parser_check_quotes(char *str);
int		parser_check_doublequote(char *str, int *dquote, int *quote);
int		parser_check_quote(char *str, int *count_quote);
char	**parser_array_clearquotes(char **arr);

//Parser_array
char	**parser_array_trim(char **str);
int		parser_array_cmp(char *str, char **arr);
int		parser_array_getsize(char **arr);
int		parser_check_valid_syntax(char **str, char **arr);

//Parser_Mem
char	*ft_free(char *ptr);
char	**ft_double_free(char **ptr, size_t size);

//Strutils
int		ft_str_clearspace_end(const char *str);
char	*ft_str_clearspace(const char *str);
char	*ft_free_strjoin(char *dst, const char *src);
char 	*ft_strappend(char *dst, char c);
int		ft_get_chrindex(const char *str, char c);
size_t	ft_wordlen(char *str, char **arr);
char	*ft_get_next_word(char *str, char **arr);
char	*ft_str_clearquotes(const char *str, char *ptr);

//utils
int		ft_error(char *err_msg, char *err_arg, int err_type);

void	array_writer(char **arr);
void	array_cleaner(char **arr);

#endif