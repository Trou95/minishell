#include "minishell.h"

int ft_freeall()
{
    int i;
    i = 0;

    if(g_data.infiles)
        free(g_data.infiles);
    if(g_data.outfiles)
        free(g_data.outfiles);
    if(g_data.heredoc)
    {
        while(i < g_data.count_her)
        {
            if(g_data.heredoc[i])
                free(g_data.heredoc[i]);
            i++;
        }
        free(g_data.heredoc);
    }
    free(g_data.pids);
    return 1;
}