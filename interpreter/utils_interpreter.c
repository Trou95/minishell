#include "minishell.h"

int ft_is_valid_env(const char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '"' && str[i] != '\'')
	{
		if(!ft_isalpha(str[i]) && !ft_isnum(str[i]) && str[i] != '_')
			return 0;
		i++;
	}
	return i;
}

char* ft_envjoin(char *dst, char* src)
{
	char *n_str;

	if(dst == NULL || src == NULL)
		return NULL;
	n_str = ft_strjoin(dst,src);
	free(dst);
	free(src);
	return n_str;
}

int ft_get_env(const char *str)
{
	int i;

	i = 0;
	while(g_env[i])
	{
		if(ft_strncmp(g_env[i],str,ft_strlen(str)) == 0)
			return i;
		i++;
	}
	return -1;
}



