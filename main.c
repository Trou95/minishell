#include "minishell.h"

int	main(int ac, char** av, char **env)
{
	char *arr[5] = {">>", "<<", ">", "<", 0};
	char *str;
	char **arg;
	ft_env_copy(env);
	while (1)
	{
		str = readline("$ >_ ");
		add_history(str);
		arg = parser_process(str);
		free(str);
		if (arg == NULL)
			continue ;
		array_writer(arg);
		ft_double_free(arg, parser_array_getsize(arg));
		//system("leaks minishell");
	}
}
