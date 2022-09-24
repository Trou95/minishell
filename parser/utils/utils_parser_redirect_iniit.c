#include "parser_utils.h"

int parser_redirect_init_vars(char *str, t_redir_var *v)
{
	ft_memset(v,0,sizeof(t_redir_var));
	v->arg_len = ft_strlen(str);
	v->cmd = ft_calloc(1,sizeof(char));
	return 1;
}

char *parser_redirect_cmdjoin(char *n_cmd, char* cmd)
{
	n_cmd = ft_free_strjoin(n_cmd, cmd);
	free(cmd);
	return n_cmd;
}