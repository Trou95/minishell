#include "minishell.h"

void	array_cleaner(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	array_writer(char **arr)
{
	int i = 0;
	while(arr[i])
	{
		printf("str[%d] => %s\n", i, arr[i]);
		i++;
	}
}
