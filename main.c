#include "minishell.h"
//env ile exp i oluştur exp'i declarele

extern t_vars	g_data;

void	all_mallocs(void)
{
	int	i;

	i = -1;
	if (g_data.count_in)
		g_data.infiles = malloc(g_data.count_in * sizeof(int));
	if (g_data.count_out)
		g_data.outfiles = malloc(g_data.count_out * sizeof(int));
	if (g_data.count_her)
	{
		g_data.heredoc = (int **)malloc(g_data.count_her * sizeof(int *));
		while (++i < g_data.count_her)
			g_data.heredoc[i] = malloc(sizeof(int) * 2);
	}
	i = -1;
	if (g_data.cmd_count)
		g_data.pids = malloc(sizeof(pid_t) * g_data.cmd_count);
}

void	assign_defaults(t_syntax_tree *tree, t_arg args)
{
	g_data.exit_num = 0;
	g_data.count_in = 0;
	g_data.count_out = 0;
	g_data.count_her = 0;
	g_data.ref_her = -1;
	g_data.interrupt = 1;
	g_data.redir_val = 1;
	g_data.cmd = -1;
	g_data.pipe = 0;
	g_data.cmd_count = args.cmd_count;
	all_redirs(tree);
	all_mallocs();
}

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	//ioctl(STDIN_FILENO, TIOCSTI, "\n");
	//write(1, "\033[A", 3);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	(void)av;
	(void)ac;
	t_syntax_tree   *tree;
	t_arg   *arg;

    g_data.env = ft_strdup_multi(envp);
    g_data.export = ft_strdup_multi(envp);
    while (1)
    { //-Wall -wextra -werror ekle makefile'ye
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ctrl_c);
        str = readline("$ >_ ");
		if(!str)
			ctrl_d();
        g_data.dup_in = dup(0);
        g_data.dup_out = dup(1);
        arg = parser_process(str, &g_data);
		//system("leaks minishell");
		if (!*str || arg == NULL) {
			free(str);
			continue ;
		}
		add_history(str);
		tree = new_tree(arg);
		assign_defaults(tree, *arg);
		all_heredocs(tree);
		if (g_data.interrupt)
		{
			if (tree->type == EXEC || tree->type == PIPE)
				executer(tree); // exec error bad address
			dup2(g_data.dup_in, 0);
			dup2(g_data.dup_out, 1);
			if (arg)
			{
				del_list(&tree);
				ft_double_free(arg->arg_commands, parser_array_getsize(arg->arg_commands));
				free(arg);
				free(str);
				//ft_freeall();
			}
		}
        //system("leaks minishell");
    }
}
//cat < Makefile > md.txt | < md.txt grep = > kerim.txt
// cat < Makefile 3-5. seferde leak: "/etc/inputrc"

/*              AÇIKLAMA:
 * new_tree ile del_listte leaks oluşmuyor.
 * new_tree func henüz tamamen doğru olmayabilir test edin ve hata durumlarını not edelim.
 *
 * tek redirection girince hatalı. CMD count 1 geldiği içim
 * Builtinler bağlanmadı
 * $?
 * builtinlerin return değerlerini g.data term değerine at
 *
 *
 *
 *
 * export yyyyyy="ssss"
zsh: segmentation fault  ./minishell
tırnak girince her şeyi tırnağa alıyor xcd
*/
