#include "minishell.h"

//parserda çift tırnak içinde boşluk varsa tırnak kaldırma
int	is_redir(char *str)
{
	int			i;
	static char	*redir_types[5] = {">>", "<<", ">", "<", 0};

	i = -1;
	while (redir_types[++i])
	{
		if (ft_strncmp(str, redir_types[i], ft_strlen(redir_types[i])) == 0)
			return (ft_strlen(redir_types[i]));
	}
	return (0);
}

char *parser_qoute_span(char *str, int *index, char c);

char *parser_qoute_join(char *dst, const char* src, int *index, char c)
{
	int len;
	char *tmp;

	len = ft_get_chrindex(&src[*index + 1],c) + (1 + (c != ' '));
	tmp = ft_substr(&src[*index], 0, len);
	dst = ft_free_strjoin(dst,ft_substr(&src[*index], 0, len));
	*index += len;
	return dst;
}

/*
char	**parser_split(char	*str)
{
	char	**ret;
	int		idx;
	int		len;
	int		line;

	ret = ft_calloc(parser_word_count(str) + 2,sizeof(char*));
	len = ft_strlen(str);
	line = -1;
	idx = 0;
	while (idx < len)
	{
		while(str[idx] == ' ')
			idx++;
		if(str[idx] == '"' || str[idx] == '\'')
		{
			ret[++line] = parser_qoute_span(str, &idx,str[idx]);
			if(str[idx] == '"' || str[idx] == '\'' || str[idx] != ' ')
			{
				if(str[idx] == '"' || str[idx] == '\'')
					ret[line] = parser_qoute_join(ret[line],str,&idx,str[idx]);
				else if(str[idx] != ' ')
					ret[line] = parser_qoute_join(ret[line], str, &idx, ' ');
			}
		}
		else if(idx <= len)
			ret[++line] = parser_qoute_span(str,&idx,' ');
	}
	return (ret);
}
*/



//word count
//space gec
char	**parser_split(char	*str)
{
	char	**ret;
	int		idx;
	int		len;
	int		line;
	char *n_str;

	n_str = ft_calloc(1, sizeof(char));
	ret = ft_calloc(parser_word_count(str) + 2,sizeof(char*));
	len = ft_strlen(str);
	if(str[len - 1] != '"' && str[len - 1] != ' ')
	{
		str = ft_free_strjoin(str," ");
	}
	line = -1;
	idx = 0;
	while(str[idx] && str[idx] == ' ')
		idx++;
	while (idx <= len)
	{
		if(str[idx] == '"' || str[idx] == '\'')
		{
			char *tmp = build_qoete(str,&idx);
			n_str = ft_free_strjoin(n_str,tmp);
			free(tmp);
		}
		else if(str[idx] > 0 && str[idx] != ' ')
		{
			char *tmp = ft_substr(str,idx,1);
			n_str = ft_free_strjoin(n_str,tmp);
			free(tmp);
			idx++;
		}
		else
		{
			ret[++line] = ft_strdup(n_str);
			ft_memset(n_str,'\0',ft_strlen(n_str));
			idx++;
		}
	}
	return (ret);
}


char	*ft_str_clearspace2(const char *str)
{
	int		i;
	char	*ret;
	char	*tmp;

	ret = ft_calloc(1,sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			tmp = ft_substr(str, i, parser_quote_endidx(&str[i + 1], '"') + 2);
			i += ft_strlen(tmp);
			ret = ft_free_strjoin(ret, tmp);
		}
		else
		{
			tmp = ft_substr(str, i, 1);
			ret = ft_free_strjoin(ret, tmp);
			i += (str[i] != ' ') + ft_str_clearspace_end(&str[i]);
		}
		free(tmp);
	}
	return (ret);
}


void	build_command(t_command	**command ,char **cmd)
{
	char **quote_cleaned_cmd;
	char **splited_cmd;

	if (!*cmd || ft_space_cntrl(*cmd))
		*command = NULL;
	else
	{
		char *tmp = ft_str_clearspace2(*cmd);
		splited_cmd = parser_split(tmp);
		int line = -1;
		printf("Splitted cmd::::\n");
		while (splited_cmd[++line])
		{
			printf("%d:%s\n", line, splited_cmd[line]);
		}
		quote_cleaned_cmd = ft_strdup_multi(splited_cmd);
		parser_array_clearquotes(quote_cleaned_cmd);
		*command = new_s_command(quote_cleaned_cmd);
		ft_double_free(splited_cmd, parser_array_getsize(splited_cmd));
		printf("cleaned & setted cmd::::\n");
		line = -1;
		while (command[0]->command[++line])
		{
			printf("%d:%s\n", line, command[0]->command[line]);
		}
	}
    printf("--------%p\n", *command);
}

int	use_is_redir(char **cmd, int *idx, char **type, int *check_redir)
{
	if (*check_redir == 1)
		return (-1);
	*type = ft_substr(cmd[0], *idx, is_redir(&(cmd[0][*idx])));
	ft_memset(&cmd[0][*idx], ' ', ft_strlen(*type));
	*idx += ft_strlen(*type);
	*check_redir = 1;
	return 0;
}

void	use_is_arg(char **cmd, int *idx, char **arg, int *check_redir)
{
	if (cmd[0][*idx] == '"' || cmd[0][*idx] == '\'')
	{
		*arg = ft_substr(cmd[0], *idx, \
						ft_get_chrindex(&cmd[0][*idx + 1], cmd[0][*idx]) + 1);
	}
	else
	{
		*arg = ft_substr(cmd[0], *idx, \
						ft_get_chrindex(&cmd[0][*idx + 1], ' ') + 1); //boşluk ya da null olmalı
	}
	ft_memset(&cmd[0][*idx], ' ', ft_strlen(*arg));
	*idx += ft_strlen(*arg);
	*check_redir = 2;
}


t_syntax_tree	*build_exec(char	*arg_command)
{
	char			*tmp_command;
	t_syntax_tree	*exec;
	t_command		*command;
	t_redirection	*redir;

	redir = NULL;
	command = NULL;
	tmp_command = ft_strdup(arg_command);
	exec = new_s_syntax_tree(EXEC);
	build_redirection(&redir, &tmp_command);
	build_command(&command ,&tmp_command);
	if (redir)
	{
		exec->right = new_s_syntax_tree(REDIR);
		exec->right->s_redir = redir;
		exec->right->prev = exec;
	}
	if (command)
	{
		exec->left = new_s_syntax_tree(COMMAND);
		exec->left->s_command = command;
		exec->left->prev = exec;
	}
	free(tmp_command);
	return (exec);
}

void	build_tree_w_pipe(t_syntax_tree *tree, char **arg_commands, int pipe_count)
{
	int	i;

	i = 0;
	while (pipe_count)
	{
		tree->left = build_exec(arg_commands[i]);
		tree->left->prev = tree;
		i++;
		pipe_count--;
		if (pipe_count)
		{
			tree->right = new_s_syntax_tree(PIPE);
			tree->right->prev = tree;
		}
		else
		{
			tree->right = build_exec(arg_commands[i]);
			tree->right->prev = tree;
		}
		tree = tree->right;
	}
}

t_syntax_tree	*new_tree(t_arg *args)
{
	t_syntax_tree	*tree;
	int				pipe_count;
	pipe_count = args->cmd_count -1;
	printf("pipe_count = %d\n", pipe_count);
	if (!pipe_count)
	{
		tree = build_exec(args->arg_commands[0]);
	}	
	else
	{

		tree = new_s_syntax_tree(PIPE);
		build_tree_w_pipe(tree, args->arg_commands, pipe_count);
	}
	return (tree);
}
