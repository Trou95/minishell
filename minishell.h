#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <errno.h>
#include "Libft/libft.h"
#include <signal.h>

#define PIPE 1
#define COMMAND 2
#define EXEC 3
#define REDIR 4

typedef struct s_arg
{
    t_command *arg_commands;
    t_redirection *arg_redirs;
    int        cmd_count;
}    t_arg;

typedef struct s_redirection
{
	char            *redir;
	char            *args;
	struct s_redirection   *next;
}   t_redirection;

typedef struct s_command
{
	char            **command;
	int is_left;
}   t_command;

typedef struct s_syntax_tree
{
	int				type;
	t_command		*s_command;
	t_redirection	*s_redir;
	struct s_syntax_tree   *left;
	struct s_syntax_tree   *right;
	struct s_syntax_tree   *prev;
}   t_syntax_tree;

typedef struct s_vars
{
	char    **env;
	char    **export;
	char    *path;
	char    *cmd_path;
	int     ret_signal;
	int		*files;
	int     fd[2];
	int		heredoc[2];
	pid_t   *pids;
}   t_vars;

typedef struct s_arg
{
	t_command *arg_commands;
	t_redirection *arg_redirs;
	int		cmd_count;
}	t_arg;


t_vars  g_data;

void    executer(t_syntax_tree *command_line);
void	sig_handler(int sig_num);
void	redirection(t_syntax_tree *tree);
void	ctrl_d();
void	del_list(t_syntax_tree *list);
void	del_s_syntax_tree(t_syntax_tree *del);
void	del_s_command(t_command *del);
void	del_s_redirection(t_redirection *del);

char    *get_path(char **env);
char	*get_cmd(char *cmd, t_vars *data);

int		ft_strcmp(char *str1, char *str2);
int		ft_filesize(t_redirection *lst);

t_syntax_tree *new_list(t_arg *args);
t_syntax_tree	*new_s_syntax_tree(int type);
t_command		*new_s_command(char **command);
t_redirection	*new_s_redirection(char *redir, char *args);

#endif
