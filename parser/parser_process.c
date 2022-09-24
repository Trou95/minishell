#include "../minishell.h"

char	**parser_process(char *str)
{
	char	**ret;
	char	**tmp;

	if (!ft_strlen(str))
		return (NULL);
	if(parser_check_quotes(str) == 0)
		return RET_ERR(ft_error("qoute error",NULL,ERR_RET));
	tmp = malloc(sizeof(char **));
	ret = malloc(sizeof(char **));
	*tmp = ft_strtrim(str, " ");
	if (*tmp == NULL)
		return (ft_double_free(tmp, 1));
	*ret = ft_str_clearspace(*tmp);
	if (*ret == NULL)
		return (ft_double_free(tmp, 1));
	ft_double_free(tmp, 1);
	tmp = parser_cmd_split(*ret, '|');
	if (tmp == NULL)
		return (ft_double_free(ret, 1));
	ft_double_free(ret, 1);
	ret = parser_array_trim(tmp);
	if (ret == NULL)
		return (ft_double_free(tmp, parser_array_getsize(tmp)));
	ft_double_free(tmp, parser_array_getsize(tmp));
	tmp = interpreter_array_format(ret);
	if(tmp == NULL)
		ft_double_free(ret, parser_array_getsize(ret));
	ret = parser_array_clearquotes(tmp);

	//ret = parser_redirect(ret);
	//ft_double_free(tmp, parser_array_getsize(tmp));
	return (ret);
}
