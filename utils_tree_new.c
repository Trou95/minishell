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

char	**parser_split(char	*str)
{
	char	**ret;
	int		idx;
	int		len;
	int		line;

	ret = ft_calloc(parser_word_count(str) + 2,sizeof(char*));
	len = ft_strlen(str) - 1;
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

void	build_command(t_command	**command ,char **cmd) {
	char **quote_cleaned_cmd;
	char **splited_cmd;

	if (!*cmd)
		*command = NULL;
	else
	{
		splited_cmd = parser_split(*cmd);
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

void	build_redirection2(t_redirection **redir, char	**cmd) //deneme amaclı
{
	int idx;
	int check_redir;
	char *type;
	char *arg;
	char *clean;
	t_redirection *tmp_redir;

	check_redir = 0;
	idx = -1;
	type = NULL;
	arg = NULL;
	while (++idx < ft_strlen(*cmd))
	{
		while (check_redir == 0 && (cmd[0][idx] == '"' || cmd[0][idx] == '\''))
			idx += parser_quote_endidx(&(cmd[0][idx + 1]), cmd[0][idx]) + 1;
		if (is_redir(&(cmd[0][idx])))
			if (use_is_redir(cmd, &idx, &type, &check_redir) == -1)
				printf("SYNTAX ERROR redir çift redir falan\n");
		if (check_redir == 1 && cmd[0][idx] != ' ' && !is_redir(&cmd[0][idx]))
			use_is_arg(cmd, &idx, &arg, &check_redir);
		if (check_redir == 2)
		{
			clean = ft_str_clearquotes(arg, ft_calloc(ft_strlen(arg) + 1,1));
			ft_lstadd_back_redir(redir, new_s_redirection(type, clean));
			type = NULL;
			arg = NULL;
			check_redir = 0;
		}
	}
	if (!*redir)
		*redir = NULL;
	else
	{
		printf("REDIR_REDIR_REDIR\n");
		tmp_redir = *redir;
		while (tmp_redir)
		{
			printf("redir type: _%s_ arg: _%s_\n", tmp_redir->redir, tmp_redir->args);
			tmp_redir = tmp_redir->next;
		}
	}
}

char *build_typer(char *str, int *index, int *check_redir)
{
	char *tmp;

	if (*check_redir == 1)
		printf("SYNTAX ERROR redir çift redir falan\n");
	tmp = ft_substr(str, *index, is_redir(&(str[*index])));
	ft_memset(&str[*index], ' ', ft_strlen(tmp));
	*index += ft_strlen(tmp);
	*check_redir = 1;
	return tmp;
}

char *build_arger(char *str, int *index, int *check_redir)
{
	char *tmp;

	if (str[*index] == '"' || str[*index] == '\'')
		tmp = ft_substr(str, *index, ft_get_chrindex(&str[*index + 1], str[*index]) + 1);
	else
		tmp = ft_substr(str, *index, ft_get_chrindex(&str[*index + 1], ' ') + 1); //boşluk ya da null olmalı
	ft_memset(&str[*index], ' ', ft_strlen(tmp));
	*index += ft_strlen(tmp);
	*check_redir = 2;
	return tmp;
}

void build_add_redirection(char *arg, char *type, t_redirection **redir, int *check_redir)
{
	char *ptr;
	char *tmp;

	ptr = ft_calloc(sizeof(char) * ft_strlen(arg) + 1,sizeof(char));
	tmp = ft_str_clearquotes(arg, ptr);
	ft_lstadd_back_redir(redir, new_s_redirection(type, tmp));
	free(arg);
	*check_redir = 0;
}

//type'ın tırkan içinde olma durumu
void	build_redirection(t_redirection **redir, char	**cmd)
{
	int		check_redir;
	char	*type;
	char	*arg;
	char *clean_arg;
	int		idx;
	t_redirection *tmp_redir;


	idx = -1;
	check_redir = 0;
	type = arg = NULL;
	while (++idx < ft_strlen(cmd[0]))
	{
		if (check_redir == 0 && (cmd[0][idx] == '"' || cmd[0][idx] == '\''))
			idx += ft_strchr(&(cmd[0][idx + 1]), cmd[0][idx]) - &(cmd[0][idx]);
		if(is_redir(&(cmd[0][idx])))
			type = build_typer(cmd[0], &idx, &check_redir);
		if (check_redir == 1 && cmd[0][idx] != ' ' && !is_redir(&cmd[0][idx]))
			arg = build_arger(cmd[0],&idx,&check_redir);
		if (check_redir == 2)
		{
			build_add_redirection(arg,type,redir,&check_redir);
			//clean_arg = ft_str_clearquotes(arg, ft_calloc(sizeof(char) * ft_strlen(arg) + 1,sizeof(char)));
			//ft_lstadd_back_redir(redir, new_s_redirection(type, clean_arg));
			type = NULL;
			//free(arg);
			arg = NULL;
			//check_redir = 0;
		}
	}
	system("leaks minishell");
	if (!*redir)
		*redir = NULL;
	else
	{
		printf("REDIR_REDIR_REDIR\n");
		tmp_redir = *redir;
		while (tmp_redir)
		{
			printf("redir type: _%s_ arg: _%s_\n", tmp_redir->redir, tmp_redir->args);
			tmp_redir = tmp_redir->next;
		}

	}
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
