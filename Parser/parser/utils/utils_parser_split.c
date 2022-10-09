/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:28:24 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 13:04:20 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

int	parser_word_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += ft_get_chrindex(&str[i + 1], str[i]);
			count++;
		}
		else if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
		}
		i++;
	}
	return (count);
}

char	*parser_qoute_span(char *str, int *index, char c)
{
	char	*tmp;

	tmp = ft_substr(&str[*index], 0, \
	ft_get_chrindex(&str[*index + 1], c) + (1 + (c != ' ')));
	*index += ft_get_chrindex(&str[*index + 1], c) + (1 + (c != ' '));
	return (tmp);
}

char	*parser_qoute_join(char *dst, const char *src, int *index, char c)
{
	int		len;
	char	*tmp;

	len = ft_get_chrindex(&src[*index + 1], c) + (1 + (c != ' '));
	tmp = ft_substr(&src[*index], 0, len);
	dst = ft_free_strjoin(dst,ft_substr(&src[*index], 0, len));
	*index += len;
	return dst;
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

char	**parser_split(char	*str)
{
	char	**ret;
	int		idx;
	int		len;
	int		line;
	char	*n_str;
	char	*tmp;

	n_str = ft_calloc(1, sizeof(char));
	ret = ft_calloc(parser_word_count(str) + 2,sizeof(char*));
	len = ft_strlen(str);
	if (str[len - 1] != '"' && str[len - 1] != ' ')
		str = ft_free_strjoin(str, " ");
	line = -1;
	idx = 0;
	while (str[idx] && str[idx] == ' ')
		idx++;
	while (idx <= len)
	{
		if (str[idx] == '"' || str[idx] == '\'')
		{
			printf("asdasdasd str: %s\n",str);
			tmp = build_quote(str, &idx);
			n_str = ft_free_strjoin(n_str, tmp);
			printf("adadas tmp: %s\n",tmp);
			free(tmp);
		}
		else if (str[idx] > 0 && str[idx] != ' ')
		{
			tmp = ft_substr(str, idx, 1);
			n_str = ft_free_strjoin(n_str, tmp);
			free(tmp);
			idx++;
		}
		else
		{
			if (!*n_str)
				break ;
			ret[++line] = ft_strdup(n_str);
			ft_memset(n_str, '\0', ft_strlen(n_str));
			idx++;
		}
	}
	return (ret);
}
