#include "../../minishell.h"

t_arg	*parser_process(char *str, char **env)
{
	t_arg	*arg;
	char	**ret;
	char	**tmp;

	if (!ft_strlen(str) || ft_space_cntrl(str))
		return (NULL);
	if (parser_check_quotes(str) == 0)
		return RET_ERR(ft_error("qoute error",NULL,ERR_RET));
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
	tmp = interpreter_array_format(ret, env);
	if (tmp == NULL)
		ft_double_free(ret, parser_array_getsize(ret));
	//ret = parser_array_clearquotes(tmp);
	ret = tmp;
	//ret = parser_redirect(ret);
	//ft_double_free(tmp, parser_array_getsize(tmp));
	arg->arg_commands = ret;
	arg->cmd_count = parser_array_getsize(ret);
	return (arg);
}
