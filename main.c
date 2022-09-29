#include "minishell.h"
//env ile exp i oluştur exp'i declarele

extern t_vars  g_data;

void    assign_defaults(t_syntax_tree *tree, t_arg args)
{
    g_data.count_in = 0;
    g_data.count_out = 0;
    g_data.count_her = 0;
    g_data.ref_her = -1;
    g_data.cmd = 0;
    g_data.cmd_count = args.cmd_count;
    all_redirs(tree);
    if (g_data.count_in)
        g_data.infiles = malloc(g_data.count_in * sizeof(int));
    if (g_data.count_out)
        g_data.outfiles = malloc(g_data.count_out * sizeof(int));
    if (g_data.count_her)
    {
        int i = -1;
        g_data.heredoc =(int **)malloc(g_data.count_her * sizeof(int *));
        while (++i < g_data.count_her)
            g_data.heredoc[i] = malloc(sizeof(int) * 2);
    }
}

int main(int ac, char **av, char **envp)
{
    char    *str;
    (void)av;
    (void)ac;
    t_syntax_tree   *tree;
    t_arg   *arg;

    g_data.env = ft_strdup_multi(envp);
    g_data.export = ft_strdup_multi(envp);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    while (1)
    {
        str = readline("$ >_ ");
		arg = parser_process(str, g_data.env);
		//system("leaks minishell");
		if (!*str || arg == NULL) {
			free(str);
			continue ;
		}
		add_history(str);
		tree = new_tree(arg);
		assign_defaults(tree, *arg);
		if (tree->type == EXEC || tree->type == PIPE)
            executer(tree); // exec error bad address
        else
            redirection(tree);
		if (arg){
			del_list(&tree);
			ft_double_free(arg->arg_commands, parser_array_getsize(arg->arg_commands));
			free(arg);
		}
		//system("leaks minishell");
    }
}