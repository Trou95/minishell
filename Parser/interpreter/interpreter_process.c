#include "minishell_interpreter.h"

char **interpreter_array_format(char **arr, char **env)
{
	int i;
	char *tmp;


	i = 0;
	while(arr[i])
	{
		tmp = ft_check_quote(arr[i], env);
		if(tmp != NULL)
		{
			free(tmp);
			tmp = arr[i];
			arr[i] = ft_check_quote(arr[i], env);
			free(tmp);
		}
		i++;
	}
	return arr;
}