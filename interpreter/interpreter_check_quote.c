#include "minishell.h"

void ft_check_quote(const char *str)
{
	int i;
	int env_len;
	char *n_str;
	char *tmp;

	i = 0;
	n_str = ft_calloc(sizeof(char),1);
	while(str[i])
	{
		if(str[i] == '"')
		{
			tmp = ft_double_quote(&str[i + 1],&i);
			n_str = ft_envjoin(n_str,tmp);
		}
		else if(str[i] == '\'')
		{
			tmp = ft_quote(&str[i + 1],&i);
			n_str = ft_envjoin(n_str,tmp);
		}
		else
		{
			if(str[i] == '$')
			{
				tmp = ft_format(&str[i + 1],&env_len);
				n_str = ft_envjoin(n_str,tmp);
				i += env_len;
			}
			else
			{
				tmp = ft_substr(str, i,1);
				n_str = ft_envjoin(n_str,tmp);
			}
		}
		i++;
	}
	printf("%s\n",n_str);
	free(n_str);
}

char* ft_double_quote(const char *str,int *end_index)
{
	int i;
	int env_len;
	char *n_str;
	char *tmp;

	i = 0;
	n_str = ft_calloc(sizeof(char),1);
	while(str[i] && str[i] != '"')
	{
		if(str[i] == '$')
		{
			tmp = ft_format(&str[i + 1],&env_len);
			n_str = ft_envjoin(n_str,tmp);
			i += ++env_len;
		}
		else
		{
			tmp = ft_substr(str, i,1);
			n_str = ft_envjoin(n_str,tmp);
			i++;
		}
	}
	*end_index += ++i;
	return n_str;
}

char* ft_quote(const char *str,int* end_index)
{
	int i;
	char *n_str;
	char *tmp;

	i = 0;
	n_str = ft_calloc(sizeof(char),1);
	while(str[i] && str[i] != '\'')
	{
		tmp = ft_substr(str,i++,1);
		n_str = ft_envjoin(n_str,tmp);
	}
	*end_index += ++i;
	return n_str;
}

char* ft_format(const char *str, int* env_len)
{
	int i;
	int index;
	char *tmp;
	char *var;

	i = ft_is_valid_env(str);
	if(i == 0)
		return 0;
	tmp = ft_substr(str, 0, i);
	var = ft_strjoin(tmp,"=");
	free(tmp);
	index = ft_get_env(var);
	if(index > -1)
	{
		*env_len = i; 
		i = ft_strlen(var);
		free(var);
		var = ft_strdup(g_env[index] + i);
		return var;
	}
	else
		free(var);
	return NULL;
}