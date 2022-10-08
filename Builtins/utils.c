#include "minishell_builtins.h"

int	free_two_str(char **s1, char **s2)
{
	if (*s1)
		free(*s1);
	if (*s2)
		free(*s2);
	return (-1);
}

void	free_char_matrix(char ***matrix)
{
	int	i;

	i = -1;
	while (matrix[0][++i])
		ft_bzero(matrix[0][i], ft_strlen(matrix[0][i]));
	i = -1;
	while (matrix[0][++i])
		free(matrix[0][i]);
	free(matrix[0]);
}

char	**ft_strdup_multi(char **s1)
{
	char	**dest;
	int		lines;
	int		i;

	i = -1;
	lines = count_line(s1);
	dest = malloc(lines * (sizeof(char *) + 1));
	while (++i < lines)
		dest[i] = ft_strdup(s1[i]);
	dest[i] = 0;
	return (dest);
}

void	print_line(char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
		printf("%s\n", lines[i]);
}

int	count_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*get_var_name(char *env)
{
	return (ft_substr(env, 0, ft_strchr(env, '=') - env + 1));
}

char	*get_var_data(char *env)
{
	int	start_i;
	int	len;

	start_i = ft_strchr(env, '=') - env + 1;
	len = ft_strlen(env) - start_i;
	return (ft_substr(env, start_i, len));
}
