#include "minishell.h"


int	ft_filesize(t_redirection *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
        if (ft_strcmp(lst, "<<"))
		    i++;
        lst = lst->next;
	}
	return (i);
}