#include "minishell.h"

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


int main(int ac, char **av, char **env)
{
 	ft_env_copy(env);
	while(1)
	{
		char *str = readline("> ");
		ft_check_quate(str);
	}
}