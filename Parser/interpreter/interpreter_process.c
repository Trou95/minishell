#include "minishell_interpreter.h"

char	**interpreter_array_format(char **arr, t_vars *g_data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		tmp = ft_check_quote(arr[i], g_data);
		if (tmp != NULL)
		{
			free(tmp);
			tmp = arr[i];
			printf("5\n");
			arr[i] = ft_check_quote(arr[i], g_data);
			printf("6\n");
			free(tmp);
		}
		i++;
	}
	array_writer(arr);
	printf("size: %d\n", parser_array_getsize(arr));
	printf("7\n");
	return (arr);
}
