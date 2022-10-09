/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:28:24 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/09 09:28:25 by gdemirta         ###   ########.tr       */
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
