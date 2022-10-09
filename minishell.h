#ifndef MINISHELL_H
# define MINISHELL_H

# include "Parser/parser/utils/parser_utils.h"
# include "Parser/interpreter/minishell_interpreter.h"
# include "Libft/libft.h"
# include "Builtins/minishell_builtins.h"
# include <fcntl.h>

t_vars  g_data;

void    executer(t_syntax_tree *command_line);
void	sig_handler(int sig_num);
void	sig_handler_heredoc(int sig_num);
void	del_list(t_syntax_tree **list);
void	del_s_syntax_tree(t_syntax_tree *del);
void	del_s_command(t_command *del);
void	del_s_redirection(t_redirection *del);
void	ft_heredoc(char *arg);
void    all_heredocs(t_syntax_tree *tree);
void	isheredoc(t_syntax_tree *tree);
void    all_redirs(t_syntax_tree *tree);
void	before_execve(t_syntax_tree *right);
void	dup_files(int *fd);
void	path_operations(char **cmd_path, t_syntax_tree *left);
void	voyage_on_tree(t_syntax_tree *tree);
void	before_execute(t_syntax_tree *tree);

int		command_w_path(char **command);
int		ctrl_d();
int		redirection(t_syntax_tree *tree);
int 	ft_space_cntrl(const char *str);


char    *get_path(char **env);
char	*get_cmd(char *cmd, char *path);

int		ft_strcmp(char *str1, char *str2);
//char	**ft_strdup_multi(char **s1);
int		ft_filesize(t_redirection *lst);
int		ft_errors(int err_num);
int		ft_matrix_size(char **matrix);
int    	ft_freeall();

int	is_redir(char *str);


void	build_redirection(t_redirection **redir, char	**cmd);
void	build_add_redirection(char *arg, char *type, t_redirection **redir, int *check_redir);
char 	*build_typer(char *str, int *index, int *check_redir);
char 	*build_arger(char *str, int *index, int *check_redir);

char 	*build_quote(char *str, int *index);
char	*build_quote_join(char *str, int *index);


t_syntax_tree	*new_list(t_arg *args);
t_syntax_tree	*new_s_syntax_tree(int type);
t_command		*new_s_command(char **command);
t_redirection	*new_s_redirection(char *redir, char *args);
t_syntax_tree	*new_tree(t_arg *args);

int	which_builtin(char **command);
int     is_builtin(char *cmd);


void	ft_lstadd_back_redir(t_redirection **redir, t_redirection *new);












#endif