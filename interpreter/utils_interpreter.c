#include "minishell_interpreter.h"

int ft_is_valid_env(const char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '"' && str[i] != '\'')
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
		i++;
	}
	return i;
}

int ft_get_env_len(const char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '"' && str[i] != '\'')
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			break;
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

void	ft_env_copy(char **env)
{
	int		i;
	int		j;
	int		len;

	len = 0;
	while(env[len])
		len++;


	g_env = ft_calloc(sizeof(char *), len + 1);
	i = -1;
	while (env[++i])
		g_env[i] = ft_calloc(sizeof(char), ft_strlen(env[i]) + 1);
	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
			g_env[i][j] = env[i][j];
	}
}



