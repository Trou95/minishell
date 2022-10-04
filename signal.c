#include "minishell.h"

int	ctrl_d(void)
{
	printf("Exit");
	exit(1);
}

void	sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig_num == SIGQUIT)
		exit(0);
	return ;
}
