#include "minishell_interpreter.h"

char	*ft_check_quote(const char *str, t_vars *g_data)
{
	int		i;
	int		env_len;
	char	*tmp[2];
	int len;

	i = -1;
	env_len = 0;
	tmp[1] = ft_calloc(sizeof(char), 1);
	len = ft_strlen(str);
	while (++i < len)
	{
		if (str[i] == '"' || str[i] == '\'')
			tmp[0] = interpreter_qouete(&str[i], str[i], &i, g_data);
		else
		{
			if (str[i] == '$')
			{
				tmp[0] = ft_format(&str[i + 1], &env_len, g_data);
				if(tmp[0] == NULL)
					tmp[0] = ft_strdup("");
				i += env_len;
			}
			else
				tmp[0] = ft_substr(str, i, 1);
		}
		tmp[1] = ft_envjoin(tmp[1], tmp[0]);
	}
	return (tmp[1]);
}

char	*ft_double_quote(const char *str, int *end_index, t_vars *g_data)
{
	int		i;
	int		env_len;
	char	*n_str;
	char	*tmp;

	i = 0;
	env_len = 0;
	n_str = ft_calloc(sizeof(char), 1);
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			tmp = ft_format(&str[i + 1], &env_len, g_data);
			if (tmp == NULL)
				tmp = ft_strdup("");
			i += ++env_len;
			//n_str = ft_envjoin(n_str, tmp);
		}
		else
			tmp = ft_substr(str, i++, 1);
		n_str = ft_envjoin(n_str, tmp);
	}
	*end_index += i;
	return (n_str);
}

char	*ft_quote(const char *str, int *end_index)
{
	int		i;
	char	*n_str;
	char	*tmp;

	i = 0;
	n_str = ft_calloc(sizeof(char), 1);
	while (str[i] && str[i] != '\'')
	{
		tmp = ft_substr(str, i++, 1);
		n_str = ft_envjoin(n_str, tmp);
	}
	*end_index += ++i;
	return (n_str);
}

char	*ft_format(const char *str, int *env_len, t_vars *g_data)
{
	int		i;
	int		index;
	char	*tmp;
	char	*var;

	if (*str == '?')
	{
		*env_len = 1;
		return ft_itoa(g_data->exit_num);
	}
	i = ft_is_valid_env(str);
	if (i == 0)
	{
		*env_len = i;
		return 0;
	}
	tmp = ft_substr(str, 0, i);
	var = ft_strjoin(tmp, "=");
	free(tmp);
	index = ft_get_env(var, g_data->env);
	if (index > -1)
	{
		*env_len = i;
		i = ft_strlen(var);
		free(var);
		var = ft_strdup(g_data->env[index] + i);
		return (var);
	}
	*env_len = i;
	free(var);
	return (NULL);
}

char	*interpreter_qouete(const char *str, char qouete, int *idx, t_vars *g_data)
{
	char	*tmp;

	if (qouete == '"')
    {

        tmp = ft_double_quote(str + 1, idx, g_data);
		printf("1:%d: _%c_ _%s_\n", *idx, str[*idx], str);
		(*idx)++; //echo "-n" asd yaması
    }
	else
		tmp = ft_quote(str + 1, idx);
    tmp = ft_strappend(tmp, qouete);
	printf("qouete tmp: %s %c\n",tmp,qouete);
	return (tmp);
}
