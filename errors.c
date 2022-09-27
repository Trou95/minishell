#include "minishell.h"

int	ft_errors(int err_num)
{
	if (err_num == 0)
		;
	exit(err_num);
}
