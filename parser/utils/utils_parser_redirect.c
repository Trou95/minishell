#include "parser_utils.h"

t_data *parser_redirect_addarg(char *command, char *redir, char *redir_arg);

int parser_redirect_check(char *str, char *arr)
{
	int i;

	i = 0;
	while(str[i] && str[i] == ' ')
		i++;
	if(!str[i])
		return 0;
	return parser_array_cmp(&str[i],arr) > -1;
}

t_data *parser_redirect_split(char *str)
{
	t_redir_var v;
	t_data *data;
	char *cmd;
	char *tmp;
	char *arg;
	int str_len;
	int len;
	char *arr[5] = {">>", "<<", ">", "<", 0};

	data = malloc(sizeof(t_data));
	cmd = malloc(sizeof(char));
	ft_memset(&v, 0, sizeof(t_redir_var));
	str_len = ft_strlen(str);
	while(v.idx < str_len)
	{
		v.arr_idx = parser_array_cmp(&str[v.idx],arr);
		if(v.arr_idx > -1)
		{
			if(parser_redirect_check(&str[v.idx + ft_strlen(arr[v.arr_idx])],arr))
			{
				printf("Syntax Error\n");
				return 0;
			}
			tmp = ft_substr(str, v.last_idx,  v.idx - v.last_idx);
			cmd = ft_free_strjoin(cmd,tmp);
			arg = ft_get_next_word(&str[v.idx + ft_strlen(arr[v.arr_idx])], arr);


			len = ft_wordlen(&str[v.idx + ft_strlen(arr[v.arr_idx])], arr) + 1;
			char ch = str[v.idx + len];
			v.idx += ft_strlen(arr[v.arr_idx]) + len;
			ch = str[v.idx];
			v.last_idx = v.idx; // + 1;

			printf("after - %s\n",&str[v.idx]);


			while(v.idx < str_len && parser_array_cmp(&str[v.idx],arr) == -1)
			{
				len = ft_wordlen(&str[v.idx],arr);
				tmp = ft_get_next_word(&str[v.idx],arr);
				cmd = ft_free_strjoin(cmd,tmp);
				if(str[v.idx + len] == ' ')
					cmd = ft_free_strjoin(cmd," ");
				v.idx += ft_wordlen(&str[v.idx],arr) + 1;
				v.last_idx = v.idx;
				printf("- %d %d %c\n",v.idx, str[v.idx],str[v.idx]);
			}
			data = parser_redirect_addarg(cmd,ft_strdup(arr[v.arr_idx]),arg);
		}
		if(str[v.idx] && parser_array_cmp(&str[v.idx],arr) == -1)
			v.idx++;
	}
	return data;
}

t_data *parser_redirect_addarg(char *command, char *redir, char *redir_arg)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->command = malloc(sizeof(t_command));
	data->redir = malloc(sizeof(t_redirection));
	data->command->command = ft_split(command,' ');
	data->redir->redir = redir;
	data->redir->args = redir_arg;
	array_writer(data->command->command);
	printf("%s => redirect\n", data->redir->redir);
	printf("%s => redirect arg\n", data->redir->args);
	return data;
}