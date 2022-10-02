#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "../../../minishell_types.h"
# include "../../../Libft/libft.h"

char	**amazing_split(char	*str);

t_arg	*parser_process(char *str, char **env);

char	*parser_qoute_spawn(char *str, int *index, char c);
int		parser_word_count(char *str);
char	**parser_cmd_split(char *str, char c);
char	**parser_split(char *str);

int		parser_quote_endidx(const char *str, char c);
int		parser_check_quotes(char *str);
int		parser_check_doublequote(char *str, int *dquote, int *quote);
int		parser_check_quote(char *str, int *count_quote);
char	**parser_array_clearquotes(char **arr);

char	**parser_array_trim(char **str);
int		parser_array_cmp(char *str, char **arr);
int		parser_array_getsize(char **arr);
int		parser_check_valid_syntax(char **str, char **arr);

char	*ft_free(char *ptr);
char	**ft_double_free(char **ptr, size_t size);

int		ft_str_clearspace_end(const char *str);
char	*ft_str_clearspace(const char *str);
char	*ft_free_strjoin(char *dst, const char *src);
char	*ft_strappend(char *dst, char c);
int		ft_get_chrindex(const char *str, char c);
size_t	ft_wordlen(char *str, char **arr);
char	*ft_get_next_word(char *str, char **arr);
char	*ft_str_clearquotes(const char *str, char *ptr);

int		ft_error(char *err_msg, char *err_arg, int err_type);

void	array_writer(char **arr);
void	array_cleaner(char **arr);

#endif