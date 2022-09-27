#include "parser_utils.h"

int	parser_word_cnt(char *str, char **arr)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (j < parser_array_getsize(arr))
		{
			if (str[i] == arr[j][0] && ft_strncmp(&str[i], arr[j], ft_strlen(arr[j])) == 0)
			{
				if(str[i + ft_strlen(arr[j])] != arr[j][0])
					count += 1;
				else
				{
					while (str[i] == arr[j][0])
						i++;
					printf("Syntax Error '%s'\n", arr[j]);
					return (-1);
				}
				i += ft_strlen(arr[j]);
				if(str[i + ft_strlen(arr[j])] == arr[j][0])
					i++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	count += 1;
	return (count);
}

int	parse_non_redir_word_count(char **str, char **arr)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (str[++i])
		size += parser_word_cnt(str[i], arr);
	return (size);
}

char	**parser_cmd_split(char *str, char c)
{
	t_redir_var	v;
	char		**commands;
	char		*tmp;

	if (str[0] == c || str[ft_strlen(str) - 1] == c)
		return (RET_ERR(ft_error(ERR_MSG_SYNTAX, "|", ERR_RET)));
	commands = malloc(sizeof(char *) * wordcounter(str, c) + 2);
	ft_memset(&v, -1, sizeof(t_redir_var));
	v.last_idx = 0;
	while (str[++v.idx])
	{
		if (str[v.idx] == '"')
			v.idx += parser_quote_endidx(&str[v.idx] + 1, str[v.idx]) + 1;
		if (str[v.idx] == c || str[v.idx + 1] == '\0')
		{
			if (str[v.idx + 1] == '\0')
				tmp = ft_substr(str, v.last_idx, v.idx + 1);
			else
				tmp = ft_substr(str, v.last_idx, v.idx - v.last_idx);
			commands[++v.n_idx] = tmp;
			v.last_idx = v.idx + 1;
		}
	}
	commands[v.n_idx + 1] = NULL;
	return (commands);
}


char **parser_redirect_split(char **str, char ***ret, char **arr)
{
	t_redir_var v;

	ft_memset(&v, 0, sizeof(t_redir_var));
	while(str[v.idx])
	{
		while (str[v.idx][v.n_idx])
		{
			v.arr_idx = parser_array_cmp(&str[v.idx][v.n_idx], arr);
			if (v.arr_idx > -1)
			{
				*((*ret) + v.k_idx) = ft_substr(str[v.idx],v.last_idx, v.n_idx - v.last_idx);
				v.last_idx = (ft_strnstr(&str[v.idx][v.last_idx], arr[v.arr_idx] ,ft_strlen(&str[v.idx][v.last_idx])) - str[v.idx]) + ft_strlen(arr[v.arr_idx]);
				v.n_idx += ft_strlen(arr[v.arr_idx]);
				v.k_idx++;
			}
			else
				v.n_idx++;
		}
		*((*ret) + v.k_idx) = ft_substr(str[v.idx], v.last_idx, ft_strlen(str[v.idx]));
		v.k_idx++;
		v.idx++;
	}
	*((*ret) + v.k_idx) = 0;
	return *ret;
}
