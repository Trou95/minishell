#ifndef _MINISHELL_TYPES_H_
#define _MINISHELL_TYPES_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

typedef struct s_redirection
{
	char					*redir;
	char					*args;
	int						her_index;
	int						in_index;
	int						out_index;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char	**command;
}	t_command;

typedef struct s_arg
{
	t_command		**arg_commands;
	t_redirection	**arg_redirs;
	int				cmd_count;
}	t_arg;

typedef struct s_syntax_tree
{
	int						type;
	t_command				*s_command;
	t_redirection			*s_redir;
	struct s_syntax_tree	*left;
	struct s_syntax_tree	*right;
	struct s_syntax_tree	*prev;
}	t_syntax_tree;

typedef struct s_vars
{
	char    **env;
	char    **export;
	char    *path;
	char    *cmd_path;
	int     ret_signal;
	int		*infiles;
	int		*outfiles;
	int		**heredoc;
	int		ref_her;
	int     fd[2];
	int		fd2[2];
	int		cmd;
	int		cmd_count;
	int 	count_in;
	int 	count_out;
	int 	count_her;
	pid_t   *pids;
}	t_vars;


typedef struct p_data
{
	t_command *command;
	t_redirection *redir;
} t_data;

typedef struct s_redir_var
{
	int idx;
	int n_idx;
	int k_idx;
	int last_idx;
	int arr_idx;
} t_redir_var;


#endif