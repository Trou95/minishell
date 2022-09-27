#include "minishell_builtins.h"

int	main(int ac, char **av, char **e)
{
	char **env;
	char **exp;
	int line;
	int tot;

	env = ft_strdup_multi(e);
	exp = ft_strdup_multi(e);
	add_declare_char_matrix(&exp);
	line = -1;
	tot = count_line(env);
	printf("");
	command_export(&exp, &env, "PATHS = asdadasd");
	command_unset(&env, &exp, "PAT");

	print_line(exp);
	printf("-------------------------------\n");
	print_line(env);
}