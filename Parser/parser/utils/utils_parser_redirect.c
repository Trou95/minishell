#include "parser_utils.h"


/*
int	parser_redirect_check(char *str, char **arr)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	return (parser_array_cmp(&str[i], arr));
}

char	**parser_redirect(char **str)
{
	int			i;
	t_data		*data;
	static char	*arr[5] = {">>", "<<", ">", "<", 0};

	i = 0;
	while (str[i])
	{
		data = parser_redirect_split(str[i], arr);
		i++;
	}
	return (str);
}

t_data	*parser_redirect_split(char *str, char **arr)
{
	t_redir_var	v;
	t_data		*data;

	parser_redirect_init_vars(str, &v);
	while (v.idx < v.arg_len)
	{
		v.arr_idx = parser_array_cmp(&str[v.idx], arr);
		if (v.arr_idx > -1)
		{
			if (parser_redirect_check(&str[v.idx + ft_strlen(arr[v.arr_idx])], arr) > -1)
				return (RET_ERR(ft_error(ERR_MSG_SYNTAX, arr[v.arr_idx], ERR_RET)));
			v.cmd = parser_redirect_cmdjoin(v.cmd, ft_substr(str, v.last_idx, v.idx - v.last_idx));
			v.arg = ft_get_next_word(&str[v.idx + ft_strlen(arr[v.arr_idx])], arr);
			v.len = ft_wordlen(&str[v.idx + ft_strlen(arr[v.arr_idx])], arr) + (str[v.idx] == ' ');
			v.idx += ft_strlen(arr[v.arr_idx]) + v.len;
			v.last_idx = v.idx;
			while (v.idx < v.arg_len && parser_array_cmp(&str[v.idx], arr) == -1)
				parser_redirect_add_cmdarg(&v, str, arr);
			data = parser_redirect_add(v.cmd, ft_strdup(arr[v.arr_idx]), v.arg);
		}
		if (str[v.idx] && parser_array_cmp(&str[v.idx], arr) == -1)
			v.idx++;
	}
	return (data);
}

t_data	*parser_redirect_add(char *command, char *redir, char *redir_arg)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->command = malloc(sizeof(t_command));
	data->redir = malloc(sizeof(t_redirection));
	data->command->command = ft_split(command, ' ');
	data->redir->redir = redir;
	data->redir->args = redir_arg;
	array_writer(data->command->command);
	printf("%s => redirect\n", data->redir->redir);
	printf("%s => redirect arg\n", data->redir->args);
	return (data);
}

int	parser_redirect_add_cmdarg(t_redir_var *v, char *str, char **arr)
{
	v->len = ft_wordlen(&str[v->idx], arr);
	if (v->idx + v->len <= v->arg_len)
		v->cmd = ft_free_strjoin(v->cmd, " ");
	v->cmd = parser_redirect_cmdjoin(v->cmd, \
		ft_get_next_word(&str[v->idx], arr));
	v->idx += ft_wordlen(&str[v->idx], arr);
	if (str[v->idx] == ' ')
		v->idx++;
	v->last_idx = v->idx;
	return (0);
}
*/
