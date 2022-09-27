#include "minishell_interpreter.h"

char* ft_check_quote(const char *str, char **env)
{
	int i;
	int env_len;
	char *tmp[2];

	i = -1;
	env_len = 0;
	tmp[1] = ft_calloc(sizeof(char),1);
	while(str[++i])
	{
		if(str[i] == '"' || str[i] == '\'')
			tmp[0] = interpreter_qouete(&str[i],str[i],&i, env);
		else
		{
			if(str[i] == '$')
			{
				tmp[0] = ft_format(&str[i + 1],&env_len, env);
				i += ++env_len;
			}
			else
				tmp[0] = ft_substr(str, i,1);
		}
		tmp[1] = ft_envjoin(tmp[1],tmp[0]);
	}
	return (tmp[1]);
}

char* ft_double_quote(const char *str,int *end_index, char **env)
{
	int i;
	int env_len;
	char *n_str;
	char *tmp;

	i = 0;
	env_len = 0;
	n_str = ft_calloc(sizeof(char),1);
	while(str[i] && str[i] != '"')
	{
		if(str[i] == '$')
		{
			tmp = ft_format(&str[i + 1],&env_len, env);
			if(tmp == NULL)
				tmp = ft_substr(str,i, ft_get_env_len(&str[i + 1]) + 1);
			i += ft_get_env_len(&str[i + 1]) + 1;
			n_str = ft_envjoin(n_str,tmp);
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

char* ft_format(const char *str, int* env_len, char **env)
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
	index = ft_get_env(var, env);
	if(index > -1)
	{
		*env_len = i; 
		i = ft_strlen(var);
		free(var);
		var = ft_strdup(env[index] + i);
		return var;
	}
	else
		free(var);
	return NULL;
}

char* interpreter_qouete(const char *str, char qouete, int* index, char **env)
{
	char *tmp;

	if(qouete == '"')
		tmp = ft_double_quote(str + 1, index, env);
	else
		tmp = ft_quote(str + 1,index);
	tmp = ft_strappend(tmp,qouete);
	return tmp;
}