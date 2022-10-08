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
		//rl_replace_line("", 0); KARABAYA SOR
		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//write(1, "\033[A", 3);
		rl_redisplay();
	}
	return ;
}

void	sig_handler_heredoc(int sig_num)
{
	if (sig_num == SIGINT)
		exit(1);
}
