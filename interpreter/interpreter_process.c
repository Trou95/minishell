#include "minishell_interpreter.h"

char **interpreter_array_format(char **arr)
{
	int i;
	char *tmp;


	i = 0;
	while(arr[i])
	{
		tmp = ft_check_quote(arr[i]);
		if(tmp != NULL)
		{
			free(tmp);
			tmp = arr[i];
			arr[i] = ft_check_quote(arr[i]);
			free(tmp);
		}
		i++;
	}
	return arr;
}