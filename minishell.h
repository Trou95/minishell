#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser/utils/parser_utils.h"
# include "interpreter/minishell_interpreter.h"
#include "libft/libft.h"

#define PIPE 1
#define COMMAND 2
#define EXEC 3
#define REDIR 4
#define LAST 10


t_vars  g_data;

void    executer(t_syntax_tree *command_line);
void	sig_handler(int sig_num);
void	redirection(t_syntax_tree *tree);
void	ctrl_d();
void	del_list(t_syntax_tree *list);
void	del_s_syntax_tree(t_syntax_tree *del);
void	del_s_command(t_command *del);
void	del_s_redirection(t_redirection *del);
void	ft_heredoc(char *arg);
void    all_heredocs(t_syntax_tree *tree);
void	isheredoc(t_syntax_tree *tree);
void    all_redirs(t_syntax_tree *tree);


char    *get_path(char **env);
char	*get_cmd(char *cmd, char *path);

int		ft_strcmp(char *str1, char *str2);
char	**ft_strdup_multi(char **s1);
int		ft_filesize(t_redirection *lst);
int		ft_errors(int err_num);
int		ft_matrix_size(char **matrix);

t_syntax_tree	*new_list(t_arg *args);
t_syntax_tree	*new_s_syntax_tree(int type);
t_command		*new_s_command(char **command);
t_redirection	*new_s_redirection(char *redir, char *args);
t_syntax_tree	*new_tree(t_arg *args);












#endif