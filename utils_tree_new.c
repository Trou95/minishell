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

char	**ft_amazing_split(char	*str)
{
	char	**ret;
	int		idx;
	int		len;
	int		line;
#define WORD_LEN 251
	ret = ft_calloc(WORD_LEN,sizeof(char*));
	len = ft_strlen(str) - 1;
	line = -1;
	idx = 0;
	while (idx < len)
	{
		while(str[idx] == ' ')
			idx++;
		if(str[idx] == '"' || str[idx] == '\'')
		{
			ret[++line] = ft_substr(&str[idx], 0 ,ft_get_chrindex(&str[idx+1], str[idx]) + 2);
			idx += ft_get_chrindex(&str[idx+1], str[idx]) + 2;
		}
		else if(idx < len)
		{
			char *tmp = ft_substr(&str[idx], 0, ft_get_chrindex(&str[idx + 1], ' ') + 1);
			ret[++line] = tmp;
			idx += ft_get_chrindex(&str[idx + 1], ' ') + 1;
		}
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
		splited_cmd = ft_amazing_split(*cmd);
		int line = -1;
		while (splited_cmd[++line])
		{
			printf("%d:%s\n", line, splited_cmd[line]);
		}
		quote_cleaned_cmd = ft_strdup_multi(splited_cmd);
		parser_array_clearquotes(quote_cleaned_cmd);
		*command = new_s_command(quote_cleaned_cmd);
		printf("COMMAND_COMMAND_cleaned\n");
		ft_double_free(splited_cmd, parser_array_getsize(splited_cmd));
	}
}
//type'ın tırkan içinde olma durumu
void	build_redirection(t_redirection **redir, char	**cmd)
{
	int		check_redir;
	char	*type;
	char	*arg;
	int		idx;
	t_redirection *tmp_redir;
	t_redir_var v;

	idx = -1;
	check_redir = 0;
	type = arg = NULL;
	while (cmd[0][++idx])
	{
		if (check_redir == 0 && cmd[0][idx] == '"')
			idx += ft_strchr(&(cmd[0][idx + 1]), '"') - &(cmd[0][idx]);
		if(is_redir(&(cmd[0][idx])))
		{
			
			if (check_redir)
				printf("SYNTAX ERROR redir çift redir falan\n");
			type = ft_substr(cmd[0], idx, is_redir(&(cmd[0][idx])));
			ft_memset(&cmd[0][idx], ' ', ft_strlen(type));
			idx += ft_strlen(type);
			check_redir = 1;
			
		}
		if (check_redir && cmd[0][idx] != ' ' && !is_redir(&cmd[0][idx]))
		{
			if (cmd[0][idx] == '"' || cmd[0][idx] == '\'')
				arg = ft_substr(cmd[0], idx, ft_strchr(&cmd[0][idx + 1], cmd[0][idx]) - &cmd[0][idx] + 1);
			else
				arg = ft_substr(cmd[0], idx, ft_get_chrindex(&cmd[0][idx + 1], ' ') + 1); //boşluk ya da null olmalı
			ft_memset(&cmd[0][idx], ' ', ft_strlen(arg));
			idx += ft_strlen(arg);
			check_redir = 0;
		}
		printf("cmd :_%s_ type: _%s_ arg: _%s_\n", *cmd, type, arg);
		if (type && arg)
		{ //tırnaklarından arındır ve kaydet
			v.cmd = ft_str_clearquotes(arg, ft_calloc(sizeof(char) * ft_strlen(arg) + 1,sizeof(char)));
			if(!*redir)
			{

				*redir = new_s_redirection(type, arg);
				tmp_redir = *redir;
				type = NULL;
				arg = NULL;
			}
			else
			{
				tmp_redir->next = new_s_redirection(type, arg);
				tmp_redir = tmp_redir->next;
				type = NULL;
				arg = NULL;
			}
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

t_syntax_tree	*build_exec(char	*arg_command)
{
	char			*tmp_cmd;
	t_syntax_tree	*exec;
	t_command		*command;
	t_redirection	*redir;

	redir = NULL;
	command = NULL;
	tmp_cmd = ft_strdup(arg_command);
	exec = new_s_syntax_tree(EXEC);
	build_redirection(&redir, &tmp_cmd);
	build_command(&command ,&tmp_cmd);
	
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
	free(tmp_cmd);
	return (exec);
}

void	build_tree_w_pipe(t_syntax_tree **tree, char **arg_commands, int pipe_count)
{
	int	i;

	i = 0;
	while (pipe_count)
	{
		tree[0]->left = build_exec(arg_commands[i]);
		tree[0]->left->prev = tree[0];
		i++;
		pipe_count--;
		if (pipe_count)
		{
			tree[0]->right = new_s_syntax_tree(PIPE);
			tree[0]->right->prev = tree[0];
		}
		else
		{
			tree[0]->right = build_exec(arg_commands[i]);
			tree[0]->right->prev = tree[0];
		}
		tree[0] = tree[0]->right;
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
		build_tree_w_pipe(&tree, args->arg_commands, pipe_count);
	}
	return (tree);
}
