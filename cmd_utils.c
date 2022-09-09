#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
		{
			if (str1[i] < str2[i])
				return (-1);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

char	*get_cmd(char *cmd, t_vars *data)
{
	char	*command;
	char	**path_list;
	int		i;

	i = -1;
	path_list = ft_split(data->path, ':');
	while (path_list[++i])
	{
		command = ft_strjoin(path_list[i], cmd, '/');
		if ((access(command, X_OK) == 0))
			return (command);
		free(command);
	}
	return (NULL);
}

char	*get_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (env[i][0] == 'P' && env[i][2] == 'T')
			return (env[i]);
	return (0);
}