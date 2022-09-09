#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)av;
    (void)ac;
    char            *str;
    t_syntax_tree   tree;

    g_data.env = envp;
    while (1)
    {
        str = readline("minishell: ");
        if (!str)
            ctrl_d();
        signal(SIGINT, sig_handler);
        signal(SIGQUIT, sig_handler);
        //lexer and parser commands
        if (tree.type == EXEC || tree.type == PIPE)
            executer(&tree);
        else
            redirection(&tree);
    }
}