#include "minishell.h"

/*void	free_char_matrix(char ***matrix)
{
	int	i;

	i = -1;
	while (matrix[0][++i])
		ft_bzero(matrix[0][i], ft_strlen(matrix[0][i]));
	i = -1;
	while (matrix[0][++i])
		free(matrix[0][i]);
	free(matrix[0]);
}*/

char	*get_path(char **env)
{
	int		line;
	char	*path;

	line = -1;
	while (env[++line])
	{
		if (!ft_strncmp(env[line], "PATH=", 5))
			break ;
	}
	if (!env[line])
		return (NULL);
	path = ft_substr(env[line], 5, ft_strlen(env[line]) - 5);
	return (path);
}

char	*get_cmd(char *cmd, char *path)
{
	char	*command;
	char	**path_list;
	char	*temp_command;
	int		i;

	i = -1;
	path_list = ft_split(path, ':');
	while (path_list[++i])
	{
		temp_command = ft_strjoin(path_list[i], "/");
		command = ft_strjoin(temp_command, cmd);
		free(temp_command);
		if ((access(command, X_OK) == 0))
		{
			free_char_matrix(&path_list);
			return (command);
		}
		free(command);
	}
	free_char_matrix(&path_list);
	return (NULL);
}
