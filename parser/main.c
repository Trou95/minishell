#include "minishell.h"

int	main(void)
{
	char *arr[5] = {">>", "<<", ">", "<", 0};
	char *str;
	char **arg;
	while (1)
	{
		str = readline("$ >_ ");
		add_history(str);
		arg = parser_process(str);
		free(str);
		if (arg == NULL)
			continue ;
		//array_writer(arg);
		ft_double_free(arg, parser_array_getsize(arg));
		system("leaks a.out");
	}
}
