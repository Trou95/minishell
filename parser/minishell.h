#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct s_redir_var
{
	int idx;
	int n_idx;
	int k_idx;
	int last_idx;
	int arr_idx;
} t_redir_var;

char **parser_redirect(char **str);
char **parser_process(char *str);

int		parser_word_cnt(char *str, char **arr);
int	parse_non_redir_word_count(char **str, char **arr);
int parser_cmd_quate_endidx(const char* str, char c);
char	**parser_cmd_split(char* str, char c);
char **parser_redirect_split(char **str, char ***ret, char **arr);

char **parser_array_trim(char **str);
int	parser_array_cmp(char *str, char **arr);
int parser_check_valid_syntax(char **str, char **arr);

int ft_array_size(char **arr);

char *ft_free(char *ptr);
char **ft_double_free(char **ptr, size_t size);

int	err_prnt(char *err_desc, char *err_code);
void	*ft_space_cntrl(const char *s, char c);

void	array_cleaner(char **arr);
void	array_writer(char **arr);






#endif