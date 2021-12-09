#include "minishell.h"

void	ft_signal_msg(int exit_code)
{
	if (exit_code == 131)
		ft_putendl_fd("QUIT: 3", 1);
	if (exit_code == 130)
		ft_putchar_fd('\n', 1);
}

void	ft_ctrl_c(int signal)
{
	(void)signal;
	if (!g_global.fork_pid)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.exit_code = 1;
	}
}

void	ft_ctrl_backslash(int signal)
{
	(void)signal;
	// if (!g_global.fork_pid)
	// {
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// }
}
