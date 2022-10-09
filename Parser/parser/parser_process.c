/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemirta <gdemirta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 01:19:21 by gdemirta          #+#    #+#             */
/*   Updated: 2022/10/10 01:19:55 by gdemirta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_arg	*parser_process(char *str, t_vars *g_data)
{
	t_arg	*arg;
	char	**ret;
	char	**tmp;

	if(parser_check_error(str) == 0)
		return NULL;
	tmp = malloc(sizeof(char **));
	ret = malloc(sizeof(char **));
	arg = malloc(sizeof(t_arg));
	*tmp = ft_strtrim(str, " ");
	if (*tmp == NULL)
		return (RET_ERR(ft_double_free(tmp, 1)));
	*ret = ft_str_clearspace(*tmp);
	if (*ret == NULL)
		return (RET_ERR(ft_double_free(tmp, 1)));
	ft_double_free(tmp, 1);
	tmp = parser_cmd_split(*ret, '|');
	if (tmp == NULL)
		return (RET_ERR(ft_double_free(ret, 1)));
	ft_double_free(ret, 1);
	ret = parser_array_trim(tmp);
	if (ret == NULL)
		return (RET_ERR(ft_double_free(tmp, parser_array_getsize(tmp))));
	ft_double_free(tmp, parser_array_getsize(tmp));
	tmp = interpreter_array_format(ret, g_data);
	if (tmp == NULL)
		ft_double_free(ret, parser_array_getsize(ret));
	ret = tmp;
	arg->arg_commands = ret;
	arg->cmd_count = parser_array_getsize(ret);
	return (arg);
}
