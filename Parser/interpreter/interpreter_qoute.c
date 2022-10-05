#include "minishell_interpreter.h"

char	*ft_check_quote(const char *str, t_vars *g_data)
{
	int		i;
	int		env_len;
	char	*tmp[2];

	i = -1;
	env_len = 0;
	tmp[1] = ft_calloc(sizeof(char), 1);
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			tmp[0] = interpreter_qouete(&str[i], str[i], &i, g_data);
		else
		{
			if (str[i] == '$')
			{
				tmp[0] = ft_format(&str[i + 1], &env_len, g_data);
				i += ++env_len;
				i -= (str[i] == '$');
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
	n_str = ft_calloc(sizeof(char), 1);
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$' && str[i + 1] != '"')
		{
			tmp = ft_format(&str[i + 1], &env_len, g_data);
			if (tmp == NULL)
				tmp = ft_substr(str, i, ft_get_env_len(&str[i + 1]) + 1);
			else if(str[i + 1] == '?')
				i += 2;
			else
			{
				i += ft_get_env_len(&str[i + 1]) + 1;
			}
			//n_str = ft_envjoin(n_str, tmp);
		}
		else
		{
			tmp = ft_substr(str, i++, 1);
			//n_str = ft_envjoin(n_str, tmp);
		}
		n_str = ft_envjoin(n_str, tmp);
	}
	*end_index += ++i;
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

	printf("1\n");
	if (*str == '?')
		return ft_itoa(g_data->exit_num);
	i = ft_is_valid_env(str);
	if (i == 0)
		return (0);
	printf("debug2\n");
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
	else
		free(var);
	return (NULL);
}

char	*interpreter_qouete(const char *str, char qouete, int *idx, t_vars *g_data)
{
	char	*tmp;

	if (qouete == '"')
		tmp = ft_double_quote(str + 1, idx, g_data);
	else
		tmp = ft_quote(str + 1, idx);
	tmp = ft_strappend(tmp, qouete);
	return (tmp);
}
